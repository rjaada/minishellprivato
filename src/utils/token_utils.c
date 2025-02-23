/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:45:18 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 19:38:11 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word_tokens(t_list_token *tokens)
{
	t_list_token	*current;
	int				count;

	count = 0;
	current = tokens;
	while (current && current->token->type == TOKEN_WORD)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	init_args_array(char ***args, int count)
{
	*args = malloc(sizeof(char *) * (count + 1));
	if (*args)
		(*args)[count] = NULL;
}

static int	copy_token_values(t_list_token *tokens, char **args, int count)
{
	t_list_token	*current;
	int				i;

	i = 0;
	current = tokens;
	while (i < count)
	{
		args[i] = ft_strdup(current->token->value);
		if (!args[i])
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}

char	**create_args_array(t_list_token *tokens)
{
	char	**args;
	int		count;

	count = count_word_tokens(tokens);
	init_args_array(&args, count);
	if (!args)
		return (NULL);
	if (!copy_token_values(tokens, args, count))
	{
		free_args_array(args, count);
		return (NULL);
	}
	return (args);
}

void	free_args_array(char **args, int count)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (i < count)
	{
		if (args[i])
			free(args[i]);
		i++;
	}
	free(args);
}
