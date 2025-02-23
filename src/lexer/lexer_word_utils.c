/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:49:27 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 21:50:11 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_quote_content(t_lexer *lexer, char quote_type, int *pos,
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

char	*get_quoted_content(t_lexer *lexer, char quote_type, int *pos)
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

char	*merge_words(char *word1, char *word2)
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

int	is_single_dollar(const char *str)
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

char	*handle_special_chars(t_lexer *lexer, char *word)
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
