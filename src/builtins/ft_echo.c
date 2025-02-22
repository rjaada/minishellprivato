/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:28:03 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:20:01 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (!str[i]);
}

static void	print_arg(char *str, int fd, int *first)
{
	if (!*first)
		ft_putchar_fd(' ', fd);
	if (!str)
		return ;
	if (str[0] == '$' && !str[1])
		ft_putchar_fd('$', fd);
	else
		ft_putstr_fd(str, fd);
	*first = 0;
}

int	echo(int ac, char **av, int fd)
{
	int	i;
	int	n_flag;
	int	first;

	if (!av)
		return (1);
	i = 0;
	n_flag = 0;
	first = 1;
	while (i < ac && av[i] && is_n_flag(av[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < ac && av[i])
	{
		print_arg(av[i], fd, &first);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', fd);
	return (0);
}
