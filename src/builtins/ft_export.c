/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:20:00 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 15:09:18 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_name(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

static int	update_env_var(char **env, char *new_var)
{
	int		i;
	char	*var_name;
	int		var_index;
	char	*dup;

	var_name = get_var_name(new_var);
	if (!var_name)
		return (0);
	var_index = find_env_var(env, var_name);
	free(var_name);
	if (var_index >= 0)
	{
		dup = ft_strdup(new_var);
		if (!dup)
			return (0);
		free(env[var_index]);
		env[var_index] = dup;
	}
	else
	{
		i = 0;
		while (env[i])
			i++;
		env[i] = ft_strdup(new_var);
		env[i + 1] = NULL;
	}
	return (1);
}

int	ft_export(char **args, char **env)
{
	int	i;
	int	ret;

	if (!args[1])
	{
		print_sorted_env(env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else if (!update_env_var(env, args[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
