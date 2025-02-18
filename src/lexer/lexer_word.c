/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:26:22 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 17:54:04 by rjaada           ###   ########.fr       */
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
		return (word1);
	if (!*word2)
	{
		free(word2);
		return (word1);
	}
	result = ft_strjoin(word1, word2);
	free(word1);
	free(word2);
	return (result);
}

static int	is_single_dollar(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] != '$')
		return (0);
	i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (!str[i]);
}

static char	*handle_special_chars(t_lexer *lexer, char *word)
{
	char	curr;
	char	*new_part;
	char	*tmp;

	curr = lexer->input[lexer->pos];
	new_part = (char *)malloc(2);
	if (!new_part)
		return (word);
	new_part[0] = curr;
	new_part[1] = '\0';
	tmp = ft_strjoin(word, new_part);
	free(word);
	free(new_part);
	lexer->pos++;
	return (tmp);
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
