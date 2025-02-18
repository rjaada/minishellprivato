/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:20:57 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:17:54 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	handle_numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

static char	*process_arg(char *arg)
{
	char	*clean_arg;
	int		len;
	char	*tmp;

	if (!arg)
		return (NULL);
	clean_arg = ft_strdup(arg);
	if (!clean_arg)
		return (NULL);
	len = ft_strlen(clean_arg);
	if (len >= 2)
	{
		if ((clean_arg[0] == '"' && clean_arg[len - 1] == '"')
			|| (clean_arg[0] == '\'' && clean_arg[len - 1] == '\''))
		{
			tmp = ft_strtrim(clean_arg, &clean_arg[0]);
			free(clean_arg);
			clean_arg = tmp;
		}
	}
	return (clean_arg);
}

static int	check_for_additional_args(char **args)
{
	int	i;
	int	has_number;

	i = 1;
	has_number = 0;
	while (args[i])
	{
		if (has_number)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		if (is_numeric(args[i]))
			has_number = 1;
		i++;
	}
	return (0);
}

int	ft_exit(char **args)
{
	long long	exit_code;
	char		*arg;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		exit(0);
	arg = process_arg(args[1]);
	if (!arg || !is_numeric(arg))
	{
		if (arg)
			free(arg);
		handle_numeric_error(args[1]);
	}
	if (check_for_additional_args(args))
	{
		free(arg);
		return (1);
	}
	exit_code = ft_atoll(arg);
	free(arg);
	exit((unsigned char)exit_code);
}
