/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/14 12:58:09 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	process_quote_content(t_lexer *lexer, char quote_type, int *pos,
		int *length)
{
	int	escaped;
	int	start;

	start = *pos;
	*length = 0;
	escaped = 0;
	while (*pos < lexer->len)
	{
		if (!escaped && lexer->input[*pos] == '\\' && *pos + 1 < lexer->len)
		{
			escaped = 1;
			(*pos)++;
			continue ;
		}
		if (!escaped && lexer->input[*pos] == quote_type)
			break ;
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
	int		escaped;
	int		i;

	content = malloc(sizeof(char) * (len + 1));
	if (!content)
		return (NULL);
	escaped = 0;
	i = 0;
	while (start < *pos)
	{
		if (!escaped && lexer->input[start] == '\\')
		{
			escaped = 1;
			start++;
			continue ;
		}
		content[i++] = lexer->input[start++];
		escaped = 0;
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
		return (NULL);
	}
	lexer->pos = pos + 1;
	if (quote_type == '"')
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
	int		len;
	char	*expanded;

	start = lexer->pos;
	while (lexer->pos < lexer->len && is_word_char(lexer->input[lexer->pos]))
		lexer->pos++;
	len = lexer->pos - start;
	word = ft_substr(lexer->input, start, len);
	if (!word)
		return (NULL);
	if (ft_strchr(word, '$'))
	{
		expanded = expand_shell_vars(word, lexer->env);
		free(word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, word));
}
