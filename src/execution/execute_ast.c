/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:41:59 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:18:27 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parsing.h"

int	execute_ast(t_ast *ast, char **env)
{
	if (ast == NULL)
		return (0);
	if (ast->type == CMD)
	{
		/* if (is_builtin(ast->value[0]))
						{g_exit_status = execute_builtin(ast->value,
								env);//handle_builtin(ast->value[0], env);
				// printf("exit status %d\n",g_exit_status);
				return ((g_exit_status));
				}*/
		// execute_command(ast->value,env);
		if (is_builtin(ast->value[0]))
		{
			g_exit_status = handle_builtin(ast->value, env);
			// printf("exit status %d\n",g_exit_status);
			return (g_exit_status);
		}
		else
		{
			g_exit_status = execute_command(ast->value, env);
			if (g_exit_status == 127)
			{
				exit(127);
			}
		}
		// free_args_array(args);
	}
	else if (ast->type == PIPE)
	{
		return (setup_pipes(ast, env));
	}
	else if (ast->type == REDIR_IN || ast->type == REDIR_OUT
		|| ast->type == APPEND)
	{
		redirection_setup(ast, env);
		//  if(ast->type == REDIR_IN)
		//{
		// red_in(ast->left->value[0]);
		//}
		// if(ast->type == REDIR_OUT)
		//{
		// red_out(ast->left->value[0]);
		//}
	}
	else
	{
		printf("cmd not found");
	}
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