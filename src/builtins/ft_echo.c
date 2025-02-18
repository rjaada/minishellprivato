/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:28:03 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 02:14:38 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

static void	print_dollar(int fd)
{
	ft_putchar_fd('$', fd);
}

static int	is_solo_dollar(char *str)
{
	return ((str[0] == '$' && (!str[1] || str[1] == ' ')) || 
		(str[0] == '"' && str[1] == '$' && str[2] == '"'));
}

static void	print_str(char *str, int fd)
{
	if (!str)
		return ;
	if (is_solo_dollar(str))
		print_dollar(fd);
	else
		ft_putstr_fd(str, fd);
}

int	echo(int ac, char **av, int fd)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (ac == 0)
		return (ft_putchar_fd('\n', fd), 0);
	while (av[i] && is_n_flag(av[i]))
	{
		n_flag = 1;
		i++;
	}
	while (av[i])
	{
		print_str(av[i], fd);
		if (av[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}

/*
int	main(int ac, char **av)
{
	if (ac >= 1)
	{
		echo(ac, (av + 1), 1);
	}
	else
		ft_putchar_fd('\n', 1);
	return (0);
}
*/