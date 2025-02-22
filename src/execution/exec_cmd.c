/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 01:23:23 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 00:20:20 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path_env(char **env)
{
	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	return (*env + 5);
}

static char	*create_cmd_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	full_path = ft_strjoin(path, cmd);
	free(path);
	return (full_path);
}

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	char	*path_env;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		full_path = create_cmd_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

int	execute_command(char **args, char **env)
{
	char	*cmd_path;
	int		status;

	if (!args || !args[0])
		return (0);
	args = skip_empty_args(args);
	if (!args[0])
		return (0);
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		status = check_file_errors(args[0]);
		if (status)
			return (status);
		cmd_path = args[0];
	}
	else
		cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
	{
		print_exec_error(args[0], ": command not found");
		return (127);
	}
	status = handle_exec(cmd_path, args, env);
	if (cmd_path != args[0])
		free(cmd_path);
	printf("\n");
	return (status);
}
