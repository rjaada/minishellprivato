/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:23:55 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/16 12:15:45 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exec_error(char *cmd)
{
	(void)cmd;
	ft_putstr_fd(" command not found\n", 2);
	//ft_putendl_fd(cmd, 2);
}

static void	child_process(char *cmd_path, char **args, char **env)
{
	execve(cmd_path, args, env);
}

int	execute_command(char **args, char **env)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
	{
		exec_error(args[0]);
		g_exit_status = 127;
		return (g_exit_status);
	}
	pid = fork();
	if (pid == 0)
		child_process(cmd_path, args, env);
	waitpid(pid, &status, 0);
	free(cmd_path);
	g_exit_status = WEXITSTATUS(status);//prohibida en 42
	return (g_exit_status);
}
