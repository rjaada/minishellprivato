/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:15:57 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/12 15:24:27 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_env_array(char **envp)
{
    int i;
    char **array_env;
    
    i = 0;
    while(envp[i])
        i++;
    array_env = malloc((i + 1) * sizeof(char *));
    if(!array_env)
        return (NULL);
    i = 0;
    while(envp[i])
    {
        array_env[i] = ft_strdup(envp[i]);
        if(!array_env[i])
        {
            while(--i)
                free(array_env[i]);
            free(array_env);
            return (NULL);   
        }    
        i ++;
    }
    array_env[i] = NULL;
    return(array_env);
}

void free_env_array(char **env)
{ 
    int i;
    
    i = 0;
    if(!env)
        return ;
    while(env[i])
    {  
        free(env[i]);
        i ++;
    }
    free(env);
}