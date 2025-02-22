/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:41:59 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/22 13:54:12 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parsing.h"

void remove_quotes(char *str)
{
    int i = 0, j = 0;
    char quote = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            if (quote == 0) 
                quote = str[i];  // Start quote
            else if (quote == str[i]) 
                quote = 0;  // End quote
            i++;
        }
        else
        {
            str[j++] = str[i++];
        }
    }
    str[j] = '\0';  // Null-terminate the modified string
}


int	execute_ast(t_ast *ast, char **env)
{
	int saved_stdin = dup(STDIN_FILENO); 
	if (ast == NULL)
		return (0);
	if (ast->type == CMD)
	{
		if (is_builtin(ast->value[0]))
		{
			g_exit_status = handle_builtin(ast->value, env);
			return (g_exit_status);
		}
		else
		{
			g_exit_status = execute_command(ast->value, env);
			if (g_exit_status == 127)
			{
				return(127);
			}
		}
	
	}
	else if (ast->type == PIPE)
	{
		return (setup_pipes(ast, env));
	}
	else if (ast->type == REDIR_OUT
		|| ast->type == APPEND )
	{
		redirection_setup(ast, env);}
     else if(ast->type == REDIR_IN)
	{
			if (red_in(ast->left->value[0]) != 0)
			{
				g_exit_status = 1;
				return (1);
			}
		execute_ast(ast->right, env);
	}
	else
	{
		printf("cmd not found");
	}
	dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);

	return (g_exit_status);
}

/*int execute_ast(t_ast *ast, char **env) {
  if (!ast) return (1);

  if (ast->type == REDIR_IN) {
		if (red_in(ast->left->value[0]) != 0) {
			g_exit_status = 1;
			return (1);
		}
		execute_ast(ast->right, env);
  } else if (ast->type == REDIR_OUT) {
		// int append = (ast->type == APPEND_OUT);
		if (red_out(ast->left->value[0]) != 0) {
			g_exit_status = 1;
			return (1);
		}
		execute_ast(ast->right, env);
  } else if (ast->type == CMD) {
		if (is_builtin(ast->value[0]))
			g_exit_status = handle_builtin(ast->value, env);
		else
			g_exit_status = execute_command(ast->value, env);
  }
  return (0);
}*/