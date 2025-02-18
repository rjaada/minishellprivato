/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:09:20 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:15:28 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_tokens(t_list_token *l_tokens)
{
	int				count;
	t_list_token	*temp;

	count = 0;
	temp = l_tokens;
	while (temp && temp->token && temp->token->type == TOKEN_WORD)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**get_args_tokens(t_list_token *l_tokens)
{
	char			**result;
	t_list_token	*temp;
	int				count;
	int				i;

	count = count_word_tokens(l_tokens);
	if (count == 0)
		return (NULL);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	temp = l_tokens;
	i = 0;
	while (i < count && temp && temp->token && temp->token->type == TOKEN_WORD)
	{
		result[i] = ft_strdup(temp->token->value);
		if (!result[i])
		{
			free_args_array(result, i);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	result[i] = NULL;
	return (result);
}
