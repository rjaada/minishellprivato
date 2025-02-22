/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:37:41 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:24:34 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	setup_pipes(t_ast *node, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	status1 = 0;
	status2 = 0;
	if (node == NULL || node->left == NULL || node->right == NULL)
	{
		return (1);
	}
	if (pipe(fd) == -1)
	{
		return (perror("error pipe"), 1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("error fork");
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(execute_ast(node->left, env));
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("error fork");
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, &status1, 0);
		return (1);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(execute_ast(node->right, env));
	}
	close(fd[0]);
	close(fd[1]);
	if (waitpid(pid1, &status1, 0) == -1)
	{
		perror("error waitpid");
		return (1);
	}
	if (waitpid(pid2, &status2, 0) == -1)
	{
		perror("error waitpid");
		return (1);
	}
	return ((status2 >> 8) & 0xFF);
}
