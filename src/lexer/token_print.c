/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:13:16 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 19:45:32 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	print_token_type(t_token *token)
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
}

static void	print_token_value(t_token *token)
{
	if (token->value)
	{
		ft_putstr_fd(" -> [", 1);
		ft_putstr_fd(token->value, 1);
		ft_putstr_fd("]", 1);
	}
	ft_putstr_fd("\n", 1);
}

void	print_token_list(t_list *list)
{
	t_token	*token;

	while (list)
	{
		token = (t_token *)list->content;
		ft_putstr_fd("Token: ", 1);
		print_token_type(token);
		print_token_value(token);
		list = list->next;
	}
}
