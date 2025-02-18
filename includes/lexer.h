/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:14:30 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/14 14:11:58 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				pos;
	int				len;
	t_list			*tokens;
	char			**env;
}					t_lexer;

/* Core lexer functions */
t_lexer				*lexer_init(char *input, char **env);
void				lexer_free(t_lexer *lexer);
t_token				*lexer_get_next_token(t_lexer *lexer);
void				lexer_skip_spaces(t_lexer *lexer);
t_list				*lexer_tokenize(t_lexer *lexer);

/* Token handling */
t_token				*token_create(t_token_type type, char *value);
void				token_free(t_token *token);
t_token				*handle_word(t_lexer *lexer);
t_token				*handle_operator(t_lexer *lexer);
t_token				*handle_quote(t_lexer *lexer, char quote_type);

/* Token list functions */
t_list				*create_token_node(void *content);
t_list				*tokenize_input(char *input, char **env);
void				print_token_list(t_list *list);

/* Utils */
int					is_operator(char c);
int					is_word_char(char c);
char				*expand_env_vars(char *str);
char				*expand_shell_vars(char *str, char **env);
char				*join_var_value(char *result, char *value);
char				*join_chars(char *str, char c);

#endif
