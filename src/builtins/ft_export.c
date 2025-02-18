/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:20:00 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 02:14:24 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var(char **env, const char *name)
{
	int	i;
	int	len;

	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && (env[i][len] == '='
				|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_identifier(const char *str)
{
	int		i;
	char	*value;

	value = ft_strchr(str, '=');
	if (value)
		*value = '\0';
	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
	{
		if (value)
			*value = '=';
		return (0);
	}
	i = 1;
	while (str[i] && (!value || str + i < value))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (value)
				*value = '=';
			return (0);
		}
		i++;
	}
	if (value)
		*value = '=';
	return (1);
}

static int	update_env_var(char **env, char *new_var)
{
	int		i;
	char	*var_name;
	int		var_index;
	char	*dup;

	var_name = ft_substr(new_var, 0, ft_strchr(new_var, '=') - new_var);
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
