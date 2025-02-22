/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:50:37 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:19:59 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
//todo
we can take different inputs in theman unset future
we  use  getcwd, chdir, and make our (setenv) function
*/

#include "minishell.h"

static void	update_env(void)
{
	char	*oldpwd;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	oldpwd = getenv("PWD");
	if (oldpwd != NULL)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", cwd, 1);
}

static int	check_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static void	print_cd_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_cd(char **args)
{
	char	*path;

	if (!args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = args[1];
	if (check_args(args))
		return (1);
	if (chdir(path) != 0)
	{
		print_cd_error(path);
		g_exit_status = 1;
		return (1);
	}
	update_env();
	g_exit_status = 0;
	return (0);
}
