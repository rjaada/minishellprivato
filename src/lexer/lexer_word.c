/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 21:49:56 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*handle_quote(t_lexer *lexer, char quote_type)
{
	char	*word;
	char	*expanded;
	int		pos;

	lexer->pos++;
	pos = lexer->pos;
	word = get_quoted_content(lexer, quote_type, &pos);
	if (!word)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		if (lexer->tokens)
			ft_lstclear(&lexer->tokens, (void *)token_free);
		return (NULL);
	}
	lexer->pos = pos + 1;
	if (quote_type == '"')
	{
		if (ft_strchr(word, '$'))
		{
			if (word[0] == '$' && !word[1])
				return (token_create(TOKEN_WORD, word));
			expanded = expand_shell_vars(word, lexer->env);
			free(word);
			return (token_create(TOKEN_WORD, expanded));
		}
	}
	return (token_create(TOKEN_WORD, word));
}

t_token	*handle_word(t_lexer *lexer)
{
	char	*word;
	char	*expanded;

	word = ft_strdup("");
	while (lexer->pos < lexer->len)
	{
		if (lexer->input[lexer->pos] == '\'' || lexer->input[lexer->pos] == '"')
		{
			expanded = handle_quote(lexer, lexer->input[lexer->pos])->value;
			word = merge_words(word, expanded);
		}
		else if (is_word_char(lexer->input[lexer->pos]))
			word = handle_special_chars(lexer, word);
		else
			break ;
	}
	if (!word)
		return (NULL);
	if (ft_strchr(word, '$') && !is_single_dollar(word))
	{
		expanded = expand_shell_vars(word, lexer->env);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}
