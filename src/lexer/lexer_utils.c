/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:27:19 by rjaada            #+#    #+#             */
/*   Updated: 2025/01/28 12:27:22 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_word_char(char c)
{
	return (!ft_isspace(c) && !is_operator(c) && c != '\'' && c != '\"'
		&& c != '\0');
}

void	token_print(t_token *token)
{
	ft_putstr_fd("Token: ", 1);
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
	else if (token->type == TOKEN_EOF)
		ft_putstr_fd("EOF", 1);
	if (token->value)
	{
		ft_putstr_fd(" -> [", 1);
		ft_putstr_fd(token->value, 1);
		ft_putstr_fd("]", 1);
	}
	ft_putstr_fd("\n", 1);
}
