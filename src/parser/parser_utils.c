/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:09:20 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 19:39:26 by rjaada           ###   ########.fr       */
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

int	size_value(char **value)
{
	int	i;

	i = 0;
	while (value[i])
		i++;
	return (i);
}

t_ast	*get_args_redirection(t_ast *node, t_list_token *l_tokens)
{
	char			**result;
	t_list_token	*temp;
	int				count;
	int				i;
	t_ast			*new_node;

	count = count_word_tokens(l_tokens);
	if (count == 0)
		return (node);
	count += size_value(node->value);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (node);
	temp = l_tokens;
	i = 0;
	while (i < size_value(node->value))
	{
		result[i] = ft_strdup(node->value[i]);
		if (!result[i])
		{
			free_args_array(result, i);
			return (node);
		}
		i++;
	}
	while (temp && temp->token && temp->token->type == TOKEN_WORD)
	{
		result[i] = ft_strdup(temp->token->value);
		if (!result[i])
		{
			free_args_array(result, i);
			return (node);
		}
		i++;
		temp = temp->next;
	}
	result[i] = NULL;
	new_node = new_ast_node(node->type, result);
	return (new_node);
}
