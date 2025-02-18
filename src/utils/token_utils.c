/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:50:29 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/06 01:15:18 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "minishell.h"

/*static void	print_token_type(t_token *token)
{
	if (token->type == TOKEN_WORD)
		ft_putstr_fd("WORD", 1);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("PIPE", 1);
	else if (token->type == TOKEN_REDIR_IN)
		ft_putstr_fd("REDIR_IN", 1);
	else if (token->type == TOKEN_REDIR_OUT)
		ft_putstr_fd("REDIR_OUT", 1);
	else if (token->type == TOKEN_HEREDOC)
		ft_putstr_fd("HEREDOC", 1);
	else if (token->type == TOKEN_APPEND)
		ft_putstr_fd("APPEND", 1);
}*/

/*void	print_token_debug(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = (t_token *)list->content;
		ft_putstr_fd("Token: ", 1);
		print_token_type(token);
		if (token->value)
		{
			ft_putstr_fd(" -> [", 1);
			ft_putstr_fd(token->value, 1);
			ft_putstr_fd("]", 1);
		}
		ft_putstr_fd("\n", 1);
		list = list->next;
	}
}*/

static int	count_word_tokens(t_list *tokens)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && ((t_token *)tmp->content)->type == TOKEN_WORD)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	**allocate_args_array(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	return (args);
}

char	**create_args_array(t_list *tokens)
{
	int		count;
	char	**args;
	int		i;
	t_token	*token;

	count = count_word_tokens(tokens);
	args = allocate_args_array(count);
	if (!args)
		return (NULL);
	i = 0;
	while (tokens && i < count)
	{
		token = (t_token *)tokens->content;
		args[i] = ft_strdup(token->value);
		i++;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

void	free_args_array(char **args)
{
	char	**args_start;

	if (!args)
		return ;
	args_start = args;
	while (*args_start)
		free(*args_start++);
	free(args);
}

int	handle_builtin(t_list *tokens, char **env)
{
	char	**args;
	int		ret;

	args = create_args_array(tokens);
	ret = 0;
	if (args && is_builtin(args[0]))
		ret = execute_builtin(args, env);
	free_args_array(args);
	return (ret);
}
