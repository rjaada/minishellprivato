/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:29:05 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 00:25:29 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"

int			g_exit_status;
/*
static int	process_input(char *input, char **env)
{
	t_list_token	*tokens;
	char			**args;

	if (syntax_error_checker(input))
	{
		g_exit_status = 2;
		return (0);
	}
	if (ft_strcmp(input, "exit") == 0)
		return (1);
	tokens = tokenize_input(input, env);
	if (!tokens)
		return (0);
	if (((t_token *)tokens->token)->type == TOKEN_WORD)
	{
		args = create_args_array(tokens);
		if (args)
		{
			if (is_builtin(args[0]))
				g_exit_status = handle_builtin(tokens, env);
			else
				g_exit_status = execute_command(args, env);
			free_args_array(args);
		}
	}
	ft_lstclear(&tokens, (void *)token_free);
	return (0);
}*/
void	print_token(t_list_token *lst)
{
	while (lst)
	{
		printf("Token: %d\n", lst->token->type);
		lst = lst->next;
	}
}
int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_list_token	*l_tokens;
	t_ast			*tree;

	(void)argc;
	(void)argv;
	// print_banner();
	setup_signal_handlers();
	g_exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		/*if (syntax_error_checker(input))
		{
		//	g_exit_status = 2;
		//	return (g_exit_status);
		}*/
		if (ft_strcmp(input, "exit") == 0)
			return (1);
		l_tokens = tokenize_input(input, env);
		if (!l_tokens)
			return (0);
		// print_token(l_tokens);
		l_tokens = tokenize_input(input, env);
		tree = parsing_tokens(l_tokens);
		generate_ast_diagram(tree);
		g_exit_status = execute_ast(tree, env);
		free(input);
	}
	return (g_exit_status);
}
