/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:25:15 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/14 14:45:59 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_var(char **env, const char *name)
{
    int i;
    size_t len;
    
    if(!env || !name)
        return (NULL);
    i = 0;
    len = ft_strlen(name);
    while(env[i])
    {
        if((ft_strncmp(env[i], name, len) == 0) && (env[i][len] == '='))
            return (env[i] + len + 1);
        i++;
    }
    return (NULL);
}

char **get_bin_path(char **env)
{
    int i;

    i = 0;
    if(env == NULL)
        return (NULL);
    while(env[i])
    {
        if(ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            return(ft_split(env[i] + 5, ':'));
        }
        i ++;
    }
    return (NULL);
}

char *get_cmd_path(char **bin_path, char *cmd)
{
    char *path;
    int i;
    char *temp;
    
    i = 0;
    if(!bin_path)
        return (NULL);
    while(bin_path[i])
    {
        temp =ft_strjoin(bin_path[i],"/");
        if(!temp)
            return (NULL);
        path = ft_strjoin(temp , cmd);
        free(temp);
        if(!path)
            return (NULL);
        if(access(path,X_OK) == 0)
            return (path);
        i ++;
    }
    free(path);
    return (NULL);
}
char *get_cmd_path_joined(char **env, char *cmd)
{
    
    return(get_cmd_path(get_bin_path(env),cmd));
}

