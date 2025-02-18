/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:19:59 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/16 11:49:54 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int  execute_cmd(t_ast *cmd, char **env)
{
    int pid;
   int status;
    (void) env;
    if(!cmd || !cmd->value)
        return 1;
    pid = fork();
    if(pid == 0)
    {
      char *path =get_cmd_path_joined(env, cmd->value[0]);
       execve(path, cmd->value, env);
       ft_putstr_fd(" command not found\n", 2);
       // perror("execv");
       g_exit_status  = 127;
        return g_exit_status;
    }
    waitpid(pid,&status,0);
    //if (WIFEXITED(g_exit_status))
      //  return WEXITSTATUS(g_exit_status);
    return g_exit_status;      
}*/
int  execute_cmd(t_ast *cmd, char **env)
{
    int pid;
    int status;

    if (!cmd || !cmd->value)
        return 1;

    pid = fork();
    if (pid == 0)
    {
        char *path = get_cmd_path_joined(env, cmd->value[0]);
        execve(path, cmd->value, env);
        ft_putstr_fd(" command not found\n", 2);
        g_exit_status = 127;
        exit(127);  // Salir con 127 si el comando no se encuentra
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))   // ⚠️ Prohibido en 42, pero te muestro para claridad
        g_exit_status = status >> 8 & 0xFF; // Usar bit-shifting en lugar de WEXITSTATUS
    return g_exit_status;
}
