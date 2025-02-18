/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:22:12 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:11:17 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_name(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(char **env, int index)
{
	if (!env[index])
		return ;
	free(env[index]);
	while (env[index + 1])
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

static int	find_var_index(char **env, const char *var)
{
	int	i;
	int	len;

	if (!var || !env)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len) && (env[i][len] == '='
				|| !env[i][len]))
			return (i);
		i++;
	}
	return (-1);
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
		if (!is_valid_name(args[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
		{
			var_index = find_var_index(env, args[i]);
			if (var_index >= 0)
				remove_env_var(env, var_index);
		}
		i++;
	}
	return (ret);
}
