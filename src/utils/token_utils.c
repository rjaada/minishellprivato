/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:45:18 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 13:15:30 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_args_array(t_list_token *tokens)
{
	t_list_token	*current;
	char			**args;
	int				count;
	int				i;

	count = 0;
	current = tokens;
	while (current && current->token->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	current = tokens;
	while (i < count)
	{
		args[i] = ft_strdup(current->token->value);
		if (!args[i])
		{
			free_args_array(args, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}

void	free_args_array(char **args, int count)
{
	int	i;

	if (!args)
		return ;
	for (i = 0; i < count; i++)
	{
		if (args[i])
			free(args[i]);
	}
	free(args);
}
