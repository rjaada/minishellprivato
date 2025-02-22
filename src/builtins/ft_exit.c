/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:20:57 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:20:04 by rjaada           ###   ########.fr       */
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
		i++;
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

static int	is_valid_number(const char *str)
{
	int			i;
	int			len;
	const char	*max_val = "9223372036854775807";
	const char	*min_val = "9223372036854775808";
	int			is_negative;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	is_negative = (str[i] == '-');
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] == '0')
		i++;
	len = 0;
	while (ft_isdigit(str[i + len]))
		len++;
	if (len > 19)
		return (0);
	if (len == 19)
	{
		if (is_negative)
			return (ft_strcmp(str + i, min_val) <= 0);
		return (ft_strcmp(str + i, max_val) <= 0);
	}
	return (1);
}

static int	parse_exit_arg(char *arg, int *exit_code)
{
	long long	num;
	int			sign;

	if (!is_numeric(arg) || !is_valid_number(arg))
		return (0);
	while (*arg && ft_isspace(*arg))
		arg++;
	sign = (*arg == '-') ? -1 : 1;
	if (*arg == '+' || *arg == '-')
		arg++;
	num = ft_atoll(arg);
	*exit_code = (num * sign) & 0xFF;
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", 2);
	if (!args[1])
		exit(0);
	if (!parse_exit_arg(args[1], &exit_code))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	exit(exit_code);
}
