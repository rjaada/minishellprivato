/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 17:09:13 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	process_quote_content(t_lexer *lexer, char quote_type, int *pos,
		int *length)
{
	int	start;

	start = *pos;
	*length = 0;
	while (*pos < lexer->len)
	{
		if (lexer->input[*pos] == quote_type)
			break ;
		(*length)++;
		(*pos)++;
	}
	if (*pos >= lexer->len)
		return (-1);
	return (start);
}

static char	*get_quoted_content(t_lexer *lexer, char quote_type, int *pos)
{
	int		start;
	int		len;
	char	*content;

	if (lexer->input[*pos] == quote_type && lexer->input[*pos
		+ 1] == quote_type)
	{
		*pos += 1;
		return (ft_strdup(""));
	}
	start = process_quote_content(lexer, quote_type, pos, &len);
	if (start == -1)
		return (NULL);
	content = ft_substr(lexer->input, start, len);
	return (content);
}

static char	*merge_words(char *word1, char *word2)
{
	char	*result;

	if (!word1)
		return (word2);
	if (!word2)
	{
		if (word1)
			return (word1);
		return (ft_strdup(""));
	}
	result = ft_strjoin(word1, word2);
	free(word1);
	free(word2);
	return (result);
}

static char	*check_next_quote(t_lexer *lexer, char *current_word)
{
	char	*quoted_part;
	char	quote_type;
	int		next_pos;

	next_pos = lexer->pos;
	while (next_pos < lexer->len && (lexer->input[next_pos] == '\''
			|| lexer->input[next_pos] == '"'))
	{
		quote_type = lexer->input[next_pos];
		lexer->pos = next_pos;
		lexer->pos++;
		quoted_part = get_quoted_content(lexer, quote_type, &lexer->pos);
		if (!quoted_part)
		{
			free(current_word);
			return (NULL);
		}
		current_word = merge_words(current_word, quoted_part);
		next_pos = ++lexer->pos;
	}
	return (current_word);
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
	if (quote_type == '"' && ft_strchr(word, '$'))
	{
		if (word[0] == '$' && (!word[1] || word[1] == ' '))
			return (token_create(TOKEN_WORD, word));
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
	char	*final_word;
	char	*expanded;

	start = lexer->pos;
	while (lexer->pos < lexer->len && is_word_char(lexer->input[lexer->pos]))
		lexer->pos++;
	word = ft_substr(lexer->input, start, lexer->pos - start);
	if (!word)
		return (NULL);
	if (word[0] == '$' && (!word[1] || word[1] == ' '))
		return (token_create(TOKEN_WORD, word));
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
