/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:19:59 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:23:12 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_ast *cmd, char **env)
{
	int		status;
	pid_t	pid;
	char	*path;

	if (!cmd || !cmd->value)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		path = get_cmd_path_joined(env, cmd->value[0]);
		execve(path, cmd->value, env);
		ft_putstr_fd(" command not found\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = status >> 8 & 0xFF;
	return (g_exit_status);
}
