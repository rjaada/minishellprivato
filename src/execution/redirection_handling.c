/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:09:25 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:24:16 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	red_in(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (perror("Error input file"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return(perror("Error redirecting stdin"), close(fd), -1);
	close(fd);
	return (0);
}

int	red_out(char *file_name)
{
	int	fd;

	if(file_name == NULL)
		return (1);
	fd = open(file_name,O_RDWR | O_CREAT | O_TRUNC,0644);
	if(fd == -1)
		return(perror("Error ouput file"),1);
	dup2(fd, STDOUT_FILENO);
	if(fd == -1)
		return(perror("Error ouput file"),close(fd),1);
	close(fd);
	return (0);
}
int	red_append(char *file_name)
{
	int	fd;

	if(file_name == NULL)
		return (1);
	fd = open(file_name,O_RDWR | O_CREAT | O_APPEND,0644);
	if(fd == -1)
		return(perror("Error ouput file"),1);
	dup2(fd, STDOUT_FILENO);
	if(fd == -1)
		return(perror("Error ouput file"),close(fd),1);
	close(fd);
	return (0);
}

void	redirection_setup(t_ast *ast, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0) {
		if (ast->type == REDIR_IN && red_in(ast->left->value[0]) == 0)
		{
			if (ast->right->type == PIPE)
				setup_pipes(ast->right, env);
			else
				execute_cmd(ast->right, env);
		}
		else if (ast->type == REDIR_OUT && red_out(ast->left->value[0]) == 0) {
			if (ast->right->type == PIPE)
				setup_pipes(ast->right, env);
			else
				execute_cmd(ast->right, env);
		}
		else if (ast->type == APPEND && red_append(ast->left->value[0]) == 0) {
			if (ast->right->type == PIPE)
				setup_pipes(ast->right, env);
			else
				execute_cmd(ast->right, env);
		}
		exit(0);
	}
	waitpid(pid, NULL, 0);
}*/
void	redirection_error(void)
{
	g_exit_status = 1;
	perror("Error redirection");
}
#include "minishell.h"

int	red_in(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (perror("Error input file"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Error redirecting stdin"), close(fd), -1);
	close(fd);
	return (0);
}

int	red_out(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (1);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error output file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Error redirecting stdout"), close(fd), 1);
	close(fd);
	return (0);
}

int	red_append(char *file_name)
{
	int	fd;

	if (file_name == NULL)
		return (1);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("Error output file"), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Error redirecting stdout"), close(fd), 1);
	close(fd);
	return (0);
}

// Helper function to get the command node from the AST
static t_ast	*get_command_node(t_ast *ast)
{
	t_ast	*cmd_node;

	cmd_node = ast;
	// Navigate through redirections to find the actual command
	while (cmd_node && (cmd_node->type == REDIR_IN
			|| cmd_node->type == REDIR_OUT || cmd_node->type == APPEND))
	{
		cmd_node = cmd_node->right;
	}
	return (cmd_node);
}

void	redirection_setup(t_ast *ast, char **env)
{
	int		pid;
	int		status;
	t_ast	*cmd_node;
	t_ast	*current;

	pid = fork();
	if (pid == 0)
	{
		// Set up all redirections first
		current = ast;
		while (current && (current->type == REDIR_IN
				|| current->type == REDIR_OUT || current->type == APPEND))
		{
			if (current->type == REDIR_IN)
			{
				if (red_in(current->left->value[0]) != 0)
				{
					g_exit_status = 1;
					// exit(g_exit_status);
					return (redirection_error());
				}
			}
			else if (current->type == REDIR_OUT)
			{
				if (red_out(current->left->value[0]) != 0)
				{
					g_exit_status = 1;
					exit(g_exit_status);
				}
			}
			else if (current->type == APPEND)
			{
				if (red_append(current->left->value[0]) != 0)
				{
					g_exit_status = 1;
					return (redirection_error());
				}
			}
			current = current->right;
		}
		// Find and execute the actual command
		cmd_node = get_command_node(ast);
		if (cmd_node)
		{
			if (cmd_node->type == PIPE)
			{
				g_exit_status = setup_pipes(cmd_node, env);
			}
			else
			{
				g_exit_status = execute_cmd(cmd_node, env);
			}
		}
		exit(g_exit_status); // Exit if command execution fails
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}
