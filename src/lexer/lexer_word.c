/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 15:22:31 by rjaada           ###   ########.fr       */
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
		return (word1);
	result = ft_strjoin(word1, word2);
	free(word1);
	free(word2);
	return (result);
}

static char	*check_next_quote(t_lexer *lexer, char *current_word)
{
	char	*next_word;
	char	*temp;

	while (lexer->pos < lexer->len && (lexer->input[lexer->pos] == '\''
			|| lexer->input[lexer->pos] == '"'))
	{
		temp = handle_quote(lexer, lexer->input[lexer->pos])->value;
		next_word = ft_strdup(temp);
		free(temp);
		if (!next_word)
		{
			free(current_word);
			return (NULL);
		}
		current_word = merge_words(current_word, next_word);
	}
	return (current_word);
}

t_token	*handle_quote(t_lexer *lexer, char quote_type)
{
	char	*word;
	char	*expanded;
	int		pos;

	lexer->pos++;
	if (lexer->input[lexer->pos] == quote_type)
	{
		lexer->pos++;
		return (token_create(TOKEN_WORD, ft_strdup("")));
	}
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
		if (word[0] == '$' && !word[1])
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
	final_word = check_next_quote(lexer, word);
	if (!final_word)
		return (NULL);
	if (final_word[0] == '$' && !final_word[1])
		return (token_create(TOKEN_WORD, final_word));
	if (ft_strchr(final_word, '$'))
	{
		expanded = expand_shell_vars(final_word, lexer->env);
		free(final_word);
		return (token_create(TOKEN_WORD, expanded));
	}
	return (token_create(TOKEN_WORD, final_word));
}
