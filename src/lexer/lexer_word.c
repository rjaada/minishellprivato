/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 15:05:52 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	process_quote_content(t_lexer *lexer, char quote_type, int *pos,
		int *length)
{
	int	start;
	int	escaped;

	start = *pos;
	*length = 0;
	escaped = 0;
	while (*pos < lexer->len)
	{
		if (!escaped && lexer->input[*pos] == quote_type)
			break ;
		if (!escaped && lexer->input[*pos] == '\\' && quote_type == '"')
		{
			escaped = 1;
			(*pos)++;
			continue ;
		}
		escaped = 0;
		(*length)++;
		(*pos)++;
	}
	if (*pos >= lexer->len)
		return (-1);
	return (start);
}

static char	*fill_quoted_content(t_lexer *lexer, int start, int *pos, int len)
{
	char	*content;
	int		i;

	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	i = 0;
	while (start < *pos)
	{
		content[i++] = lexer->input[start++];
	}
	content[i] = '\0';
	return (content);
}

static char	*get_quoted_content(t_lexer *lexer, char quote_type, int *pos)
{
	int	start;
	int	len;

	start = process_quote_content(lexer, quote_type, pos, &len);
	if (start == -1)
		return (NULL);
	return (fill_quoted_content(lexer, start, pos, len));
}

static char	*handle_empty_quotes(t_lexer *lexer, char quote_type)
{
	if (lexer->input[lexer->pos] == quote_type && lexer->input[lexer->pos
		+ 1] == quote_type)
	{
		lexer->pos += 2;
		return (ft_strdup(""));
	}
	return (NULL);
}

t_token	*handle_quote(t_lexer *lexer, char quote_type)
{
	char	*word;
	char	*expanded;
	int		pos;

	lexer->pos++;
	word = handle_empty_quotes(lexer, quote_type);
	if (word)
		return (token_create(TOKEN_WORD, word));
	pos = lexer->pos;
	word = get_quoted_content(lexer, quote_type, &pos);
	if (!word)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (NULL);
	}
	lexer->pos = pos + 1;
	if (quote_type == '"' && ft_strchr(word, '$'))
	{
		expanded = expand_shell_vars(word, lexer->env);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}

t_token	*handle_word(t_lexer *lexer)
{
	int		start;
	char	*word;
	char	*expanded;

	start = lexer->pos;
	while (lexer->pos < lexer->len && is_word_char(lexer->input[lexer->pos]))
		lexer->pos++;
	word = ft_substr(lexer->input, start, lexer->pos - start);
	if (!word)
		return (NULL);
	if (word[0] == '$' && !word[1])
		return (token_create(TOKEN_WORD, word));
	if (ft_strchr(word, '$'))
	{
		expanded = expand_shell_vars(word, lexer->env);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}
