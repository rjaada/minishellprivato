/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:08:12 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 19:46:06 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*join_chars(char *str, char c)
{
	str = str_join_char(str, c);
	return (str);
}

char	*join_var_value(char *result, char *value)
{
	char	*tmp;

	if (!value)
		return (result);
	tmp = result;
	result = ft_strjoin(result, value);
	free(tmp);
	return (result);
}
