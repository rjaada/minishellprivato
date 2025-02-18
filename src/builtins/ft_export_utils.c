/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:20:30 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 13:11:20 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env_array(char **env, int size)
{
	char	**sorted;
	int		i;

	sorted = malloc(sizeof(char *) * (size + 1));
	if (!sorted)
		return (NULL);
	i = -1;
	while (++i < size)
		sorted[i] = env[i];
	sorted[i] = NULL;
	return (sorted);
}

static void	sort_env_array(char **sorted, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - 1 - i)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
		}
	}
}

void	print_sorted_env(char **env)
{
	char	**sorted;
	int		size;
	int		i;

	size = 0;
	while (env[size])
		size++;
	sorted = dup_env_array(env, size);
	if (!sorted)
		return ;
	sort_env_array(sorted, size);
	i = -1;
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sorted[i], 1);
	}
	free(sorted);
}

int	get_env_size(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}
