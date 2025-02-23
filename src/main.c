/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:29:05 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 22:00:50 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"

int			g_exit_status;

static void	cleanup_resources(char *input, t_list_token *tokens)
{
	ft_lstclear(&tokens, (void *)token_free);
	free(input);
}

static int	handle_exit_command(char *input)
{
	if (ft_strcmp(input, "exit") == 0)
	{
		free(input);
		return (1);
	}
	return (0);
}

static int	process_input(char *input, char **env)
{
	t_list_token	*l_tokens;
	t_ast			*tree;

	if (syntax_error_checker(input))
	{
		g_exit_status = 2;
		free(input);
		return (0);
	}
	l_tokens = tokenize_input(input, env);
	if (!l_tokens)
	{
		free(input);
		return (0);
	}
	tree = parsing_tokens(l_tokens);
	if (!tree)
	{
		cleanup_resources(input, l_tokens);
		return (0);
	}
	g_exit_status = execute_ast(tree, env);
	cleanup_resources(input, l_tokens);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	print_banner();
	setup_signal_handlers();
	g_exit_status = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input && *input)
			add_history(input);
		if (handle_exit_command(input))
			return (1);
		process_input(input, env);
	}
	return (g_exit_status);
}
