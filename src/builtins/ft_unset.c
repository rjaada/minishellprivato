/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:12 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 21:18:33 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(char **env, int index)
{
	free(env[index]);
	while (env[index + 1])
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

static int	is_system_var(const char *name)
{
	static const char	*system_vars[] = {"HOME", "PATH", "SHELL", NULL};
	int					i;

	i = 0;
	while (system_vars[i])
	{
		if (!ft_strcmp(name, system_vars[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, char **env)
{
	int	i;
	int	ret;
	int	var_index;

	if (!args || !args[1] || !env)
		return (0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else if (!is_system_var(args[i]))
		{
			var_index = find_env_var(env, args[i]);
			if (var_index >= 0)
				remove_env_var(env, var_index);
		}
		i++;
	}
	return (ret);
}
