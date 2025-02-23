/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:23:55 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 21:05:59 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_exec_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(msg, 2);
}

int	check_file_errors(char *cmd)
{
	struct stat	st;

	if (!cmd || !*cmd)
		return (0);
	if ((cmd[0] == '/' || cmd[0] == '.') && stat(cmd, &st) != 0)
	{
		print_exec_error(cmd, ": No such file or directory");
		return (127);
	}
	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_exec_error(cmd, ": Is a directory");
			return (126);
		}
		if (access(cmd, X_OK) != 0)
		{
			print_exec_error(cmd, ": Permission denied");
			return (126);
		}
		return (0);
	}
	return (127);
}

int	handle_exec(char *cmd_path, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, env) == -1)
			exit(127);
	}
	waitpid(pid, &status, 0);
	return ((status >> 8) & 0xFF);
}

char	**skip_empty_args(char **args)
{
	int	i;
	int	j;

	if (!args || !args[0])
		return (args);
	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			args[j++] = args[i];
		i++;
	}
	args[j] = NULL;
	return (args);
}
