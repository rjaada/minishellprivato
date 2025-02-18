/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 13:15:33 by rjaada           ###   ########.fr       */
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
		if (!escaped && lexer->input[*pos] == '\\' && quote_type == '"')
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

static char	*check_next_quote(t_lexer *lexer, char *current_word)
{
	int		next_pos;
	char	*quoted_part;
	char	*result;
	char	quote_type;

	next_pos = lexer->pos;
	if (next_pos >= lexer->len || (lexer->input[next_pos] != '"'
			&& lexer->input[next_pos] != '\''))
		return (current_word);
	quote_type = lexer->input[next_pos];
	lexer->pos++;
	next_pos = lexer->pos;
	quoted_part = get_quoted_content(lexer, quote_type, &next_pos);
	if (!quoted_part)
	{
		free(current_word);
		return (NULL);
	}
	result = ft_strjoin(current_word, quoted_part);
	free(current_word);
	free(quoted_part);
	lexer->pos = next_pos + 1;
	return (result);
}

t_token	*handle_quote(t_lexer *lexer, char quote_type)
{
	char	*word;
	char	*expanded;
	char	*result;
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
	result = check_next_quote(lexer, word);
	if (!result)
		return (NULL);
	if (quote_type == '"')
	{
		expanded = expand_shell_vars(result, lexer->env);
		free(result);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, result));
}

t_token	*handle_word(t_lexer *lexer)
{
	int		start;
	char	*word;
	int		len;
	char	*expanded;
	char	*final_word;

	start = lexer->pos;
	while (lexer->pos < lexer->len && is_word_char(lexer->input[lexer->pos]))
		lexer->pos++;
	len = lexer->pos - start;
	word = ft_substr(lexer->input, start, len);
	if (!word)
		return (NULL);
	final_word = check_next_quote(lexer, word);
	if (!final_word)
		return (NULL);
	if (ft_strchr(final_word, '$'))
	{
		expanded = expand_shell_vars(final_word, lexer->env);
		free(final_word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, final_word));
}
