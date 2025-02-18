/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:20:57 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 02:14:31 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** check if the input is exit
//to do      i have to ignore the spaces caracters after exit word

*/
#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
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

	len = ft_strlen(arg);
	if ((arg[0] == '"' && arg[len - 1] == '"') || (arg[0] == '\'' && arg[len
			- 1] == '\''))
		clean_arg = ft_strtrim(arg, &arg[0]);
	else
		clean_arg = ft_strdup(arg);
	return (clean_arg);
}

static int	handle_args(char **args)
{
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
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
	if (handle_args(args))
		return (1);
	arg = process_arg(args[1]);
	if (!is_numeric(arg))
		handle_numeric_error(args[1]);
	exit_code = ft_atoll(arg);
	free(arg);
	exit((unsigned char)exit_code);
}
