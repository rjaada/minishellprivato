/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:25:19 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 00:24:42 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_quote_counts(char c, int *s_q, int *d_q)
{
	if (c == '\'')
		(*s_q)++;
	else if (c == '\"')
		(*d_q)++;
}

static int	is_valid_filename_char(char c)
{
	return (c != '\0' && !ft_isspace(c) && c != '<' && c != '>' && c != '|'
		&& c != '\'' && c != '\"');
}

static int	check_redirection_token(const char **input)
{
	char	current;
	int		count;

	current = **input;
	count = 1;
	while ((*input)[count] == current)
	{
		if (count > 1)
			return (0);
		count++;
	}
	*input += count;
	return (1);
}

static int	skip_to_filename(const char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
	return (is_valid_filename_char(**input));
}

int	check_redirection(const char **input)
{
	if (!check_redirection_token(input))
		return (0);
	return (skip_to_filename(input));
}
