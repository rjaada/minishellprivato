/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:41:59 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/20 15:04:37 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "parsing.h"



// Structure to track redirection state
typedef struct s_redir_state {
    char    *input_file;     // Current input redirection file
    char    **cmd_args;      // Command arguments
    int     has_file_args;   // Whether command has file arguments
    int     saved_stdin;     // Saved stdin for restoration
    char    **env;           // Environment variables
} t_redir_state;

// Function to handle error messages and exit codes
void handle_redir_error( char *file, char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(msg, 2);
    g_exit_status = 1;
}

// Function to handle input redirection setup
int setup_input_redirection(char *file)
{
    int fd;
    char *trimmed_file = ft_strtrim(file, "\"'");
    
    if (!trimmed_file)
        return (1);
        
    fd = open(trimmed_file, O_RDONLY);
    free(trimmed_file);
    
    if (fd == -1)
    {
        handle_redir_error(file, strerror(errno));
        return (1);
    }
    
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

// Function to execute command with redirection
int execute_redirected_command(t_redir_state *state)
{
    if (!state->cmd_args || !state->cmd_args[0])
        return (1);

    // If command has file arguments, ignore input redirection
    if (state->has_file_args)
        return (execute_command(state->cmd_args, state->env));

    // Set up input redirection
    if (state->input_file)
    {
        if (setup_input_redirection(state->input_file) != 0)
            return (1);
    }

    return (execute_command(state->cmd_args, state->env));
}

// Modified execute_ast function
int execute_ast(t_ast *ast, char **env)
{
    t_redir_state state = {0};
    state.saved_stdin = dup(STDIN_FILENO);
    state.env = env;

    if (ast == NULL)
        return (0);

    if (ast->type == CMD)
    {
        if (is_builtin(ast->value[0]))
            g_exit_status = handle_builtin(ast->value, env);
        else
        {
            state.cmd_args = ast->value;
            state.has_file_args = (ast->value[1] != NULL);
            g_exit_status = execute_redirected_command(&state);
        }
    }
    else if (ast->type == PIPE)
    {
        return (setup_pipes(ast, env));
    }
    else if (ast->type == REDIR_IN)
    {
        // Handle input redirection
        if (ast->left && ast->left->value)
        {
            state.input_file = ast->left->value[0];
            if (ast->right)
            {
                if (ast->right->type == CMD)
                {
                    state.cmd_args = ast->right->value;
                    state.has_file_args = (ast->right->value[1] != NULL);
                    g_exit_status = execute_redirected_command(&state);
                }
                else
                {
                    if (setup_input_redirection(state.input_file) == 0)
                        execute_ast(ast->right, env);
                }
            }
        }
    }
    else if (ast->type == REDIR_OUT || ast->type == APPEND)
    {
        redirection_setup(ast, env);
    }

    // Restore stdin
    dup2(state.saved_stdin, STDIN_FILENO);
    close(state.saved_stdin);

    return (g_exit_status);
}