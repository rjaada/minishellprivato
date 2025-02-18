/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:02:40 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 13:20:56 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include "builtins.h"
# include "lexer.h"
# include "parsing.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define RESET "\033[0m"
# define BLACK "\033[30m"              /* Black */
# define RED "\033[31m"                /* Red */
# define GREEN "\033[32m"              /* Green */
# define YELLOW "\033[33m"             /* Yellow */
# define BLUE "\033[34m"               /* Blue */
# define MAGENTA "\033[35m"            /* Magenta */
# define CYAN "\033[36m"               /* Cyan */
# define WHITE "\033[37m"              /* White */
# define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
# define BOLDRED "\033[1m\033[31m"     /* Bold Red */
# define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
# define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
# define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
# define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

extern int				g_exit_status;

/* Structs */

typedef struct s_cmd
{
	char				*cmd;
	char				**args;
	char				*input;
	char				*output;
}						t_cmd;

typedef struct s_data
{
	char				*input;
	char				**tokens;
	char				**env_vars;
	char				*old_pwd;
	char				*pwd;

	t_cmd				*cmd;
}						t_data;

typedef struct s_ast
{
	t_type_node			type;
	char				**value;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_list_token
{
	t_token				*token;
	struct s_list_token	*next;
}						t_list_token;

/* Forward declarations */
typedef struct s_token	t_token;

/* Signal handling */
void					setup_signal_handlers(void);
void					handle_ctrl_c(int sig_num);
void					child_ctrl_c(int sig_num);

/* Input validation */
int						syntax_error_checker(const char *input);
int						has_unclosed_quotes(const char *input);
int						has_invalid_redirections(const char *input);
int						has_misplaced_operators(const char *input);
int						has_logical_operators(const char *input);
void					update_quote_counts(char c, int *s_q, int *d_q);
int						is_invalid_operator(const char **input);

/* String utils */
char					*str_join_char(char *str, char c);
char					*str_join_free(char *s1, char *s2);
int						str_is_empty(char *str);
void					str_free_array(char **array);

/* Error utils */
void					*error_malloc(void);
void					print_error(char *msg);

/* Memory utils */
void					*safe_malloc(size_t size);
void					safe_free(void *ptr);
void					safe_free_array(char **array);

/* Print banner */
void					print_banner(void);

/* Builtin execution */
int						is_builtin(char *cmd);
int						handle_builtin(char **args, char **env);
char					**create_args_array(t_list_token *tokens);
void					free_args_array(char **args, int count);

/* Execution */
int						execute_command(char **args, char **env);
void					free_array(char **arr);
char					*find_command_path(char *cmd, char **env);

void					generate_ast_diagram(t_ast *root);

#endif
