/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:28:03 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:17:20 by rjaada           ###   ########.fr       */
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

static int	is_standalone_dollar(char *str)
{
	return (str && str[0] == '$' && !str[1]);
}

static void	print_str(char *str, int fd)
{
	if (!str)
		return ;
	if (is_standalone_dollar(str))
		print_dollar(fd);
	else
		ft_putstr_fd(str, fd);
}

static int	should_add_space(char **av, int current_index)
{
	if (!av[current_index + 1])
		return (0);
	return (1);
}

int	echo(int ac, char **av, int fd)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (ac == 0)
	{
		ft_putchar_fd('\n', fd);
		return (0);
	}
	while (av[i] && is_n_flag(av[i]))
	{
		n_flag = 1;
		i++;
	}
	while (av[i])
	{
		print_str(av[i], fd);
		if (should_add_space(av, i))
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
