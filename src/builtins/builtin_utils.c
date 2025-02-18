/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:09:56 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/18 15:10:04 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export"));
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	handle_builtin(char **args, char **env)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		return (echo(count_args(args) - 1, args + 1, 1));
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (pwd(count_args(args) - 1));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(env, 1, env));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, env));
	if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args));
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, env));
	return (1);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_var(char **env, const char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (-1);
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
