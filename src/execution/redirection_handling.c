/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:09:25 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/17 16:07:26 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int red_in(char *file_name)
{
    int fd;
    
    fd = open(file_name, O_RDONLY);
    if (fd == -1)
        return (perror("Error input file"), -1);
    if (dup2(fd, STDIN_FILENO) == -1)
        return(perror("Error redirecting stdin"), close(fd), -1);
    close(fd); 
    return 0;
}

int red_out(char *file_name)
{
    int fd;
    
    if(file_name == NULL)
        return (1);
    fd = open(file_name,O_RDWR | O_CREAT | O_TRUNC,0644);
    if(fd == -1)
        return(perror("Error ouput file"),1);
    dup2(fd, STDOUT_FILENO);
    if(fd == -1)
        return(perror("Error ouput file"),close(fd),1);
    close(fd);
    return (0);
}
int red_append(char *file_name)
{
    int fd;
    
    if(file_name == NULL)
        return (1);
    fd = open(file_name,O_RDWR | O_CREAT | O_APPEND,0644);
    if(fd == -1)
        return(perror("Error ouput file"),1);
    dup2(fd, STDOUT_FILENO);
    if(fd == -1)
        return(perror("Error ouput file"),close(fd),1);
    close(fd);
    return (0);
}



void redirection_setup(t_ast *ast, char **env)
{
    int pid = fork();
    if (pid == 0) {
        if (ast->type == REDIR_IN && red_in(ast->left->value[0]) == 0) 
        {
            if (ast->right->type == PIPE)
                setup_pipes(ast->right, env);
            else
                execute_cmd(ast->right, env);
        }
        else if (ast->type == REDIR_OUT && red_out(ast->left->value[0]) == 0) {
            if (ast->right->type == PIPE)
                setup_pipes(ast->right, env);
            else
                execute_cmd(ast->right, env);
        }
        else if (ast->type == APPEND && red_append(ast->left->value[0]) == 0) {
            if (ast->right->type == PIPE)
                setup_pipes(ast->right, env);
            else
                execute_cmd(ast->right, env);
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
}
