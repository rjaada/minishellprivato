/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:14:06 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 19:46:35 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quotes(const char *input)
{
	char	quote_type;

	quote_type = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (quote_type == *input)
				quote_type = 0;
			else if (!quote_type)
				quote_type = *input;
		}
		input++;
	}
	return (quote_type != 0);
}

int	has_invalid_redirections(const char *input)
{
	int	s_q_count;
	int	d_q_count;

	s_q_count = 0;
	d_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if ((!(s_q_count % 2) && !(d_q_count % 2)) && (*input == '>'
				|| *input == '<'))
		{
			if (!check_redirection(&input))
				return (1);
		}
		else
			input++;
	}
	return (0);
}

int	has_misplaced_operators(const char *input)
{
	int	s_q_count;
	int	d_q_count;
	int	expect_cmd;

	s_q_count = 0;
	d_q_count = 0;
	expect_cmd = 0;
	while (*input && ft_isspace(*input))
		input++;
	if (*input == '|' || *input == '&')
		return (1);
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if (*input == '|' && !(s_q_count % 2) && !(d_q_count % 2))
		{
			if (expect_cmd)
				return (1);
			expect_cmd = 1;
		}
		else if (!ft_isspace(*input))
			expect_cmd = 0;
		input++;
	}
	return (expect_cmd);
}

int	has_logical_operators(const char *input)
{
	int	s_q_count;
	int	d_q_count;

	s_q_count = 0;
	d_q_count = 0;
	while (*input)
	{
		update_quote_counts(*input, &s_q_count, &d_q_count);
		if (!(d_q_count % 2) && !(s_q_count % 2) && ((*input == '&' && *(input
						+ 1) == '&') || (*input == '|' && *(input + 1) == '|')))
			return (1);
		input++;
	}
	return (0);
}

int	syntax_error_checker(const char *input)
{
	const char	*last = input + ft_strlen(input) - 1;

	if (has_unclosed_quotes(input))
		return (0);
	while (*input && ft_isspace(*input))
		input++;
	if (*input == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (last > input && ft_isspace(*last))
		last--;
	if (*last == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}
