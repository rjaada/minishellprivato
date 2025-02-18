/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:09:37 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/13 23:44:52 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// i should be crerate struct shell with env or use g_env
// and add in struct shell fd_in and fd_out  to use it in ft_putstr_fd
int	ft_env(char **arg, int fd, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	(void)arg;
	return (1);
}
