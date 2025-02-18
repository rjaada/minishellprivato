/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:25:33 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/13 23:43:50 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_init(char *input, char **env)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	lexer->tokens = NULL;
	lexer->env = env;
	return (lexer);
}

void	lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->tokens)
		ft_lstclear(&lexer->tokens, (void *)token_free);
	free(lexer);
}

void	lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && ft_isspace(lexer->input[lexer->pos]))
		lexer->pos++;
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	if (!lexer || lexer->pos >= lexer->len)
		return (token_create(TOKEN_EOF, NULL));
	lexer_skip_spaces(lexer);
	if (lexer->pos >= lexer->len)
		return (token_create(TOKEN_EOF, NULL));
	if (is_operator(lexer->input[lexer->pos]))
		return (handle_operator(lexer));
	if (lexer->input[lexer->pos] == '\'' || lexer->input[lexer->pos] == '\"')
		return (handle_quote(lexer, lexer->input[lexer->pos]));
	return (handle_word(lexer));
}
