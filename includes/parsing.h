/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:26:00 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/23 00:17:11 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"
# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_list_token	t_list_token;

typedef enum e_type_node
{
	CMD,
	PIPE,
	FILENAME,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}							t_type_node;

void						ft_lstadd_back(t_list_token **lst,
								t_list_token *new);
void						ft_lstadd_front(t_list_token **lst,
								t_list_token *new);
void						ft_lstclear(t_list_token **lst,
								void (*del)(void *));
void						ft_lstdelone(t_list_token *lst,
								void (*del)(void *));
void						ft_lstiter(t_list_token *lst, void (*f)(void *));
t_list_token				*ft_lstlast(t_list_token *lst);
t_list_token				*ft_lstmap(t_list_token *lst, void *(*f)(void *),
								void (*del)(void *));
t_list_token				*ft_lstnew(void *content);
int							ft_lstsize(t_list_token *lst);

t_ast						*parsing_tokens(t_list_token *l_tokens);
char						**get_args_tokens(t_list_token *l_tokens);
void						generate_ast_diagram(t_ast *root);
int							execute_ast(t_ast *ast, char **env);
int							execute_cmd(t_ast *cmd, char **env);
int							setup_pipes(t_ast *node, char **env);
char						**create_env_array(char **envp);

char						*get_env_var(char **env, const char *name);
char						*get_cmd_path(char **bin_path, char *cmd);
char						**get_bin_path(char **env);
char						*get_cmd_path_joined(char **env, char *cmd);
int							red_in(char *file_name);
int							red_out(char *file_name);
void						redirection_setup(t_ast *ast, char **env);

//**************** */
void						free_array(char **arr);
int							execute_command(char **args, char **env);
char						*find_command_path(char *cmd, char **env);
//**************** */

void						generate_ast_diagram(t_ast *root);
t_ast						*get_args_redirection(t_ast *node,
								t_list_token *l_tokens);
t_ast						*new_ast_node(t_type_node type, char **value);

#endif