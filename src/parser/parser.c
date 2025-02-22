/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoundir <kmoundir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:37:05 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/22 13:17:23 by kmoundir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_type_node type, char **value)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
static t_list_token	*move_to_operator(t_list_token *l_tokens)
{
	while (l_tokens->token->type == TOKEN_WORD && l_tokens && l_tokens->token)
		l_tokens = l_tokens->next;
	return (l_tokens);
}

t_ast	*parsing_tokens(t_list_token *l_tokens)
{
	t_ast	*root;
	t_ast	*current;
	t_ast	*cmd_node;
	t_ast	*pipe_node;
	t_ast	*red;

	root = NULL;
	current = NULL;
	if (!l_tokens)
		return (NULL);
	while (l_tokens && l_tokens->token && l_tokens->token->value)
	{
		if (l_tokens->token->type == TOKEN_WORD)
		{
			cmd_node = new_ast_node(CMD, get_args_tokens(l_tokens));
			l_tokens = move_to_operator(l_tokens);
			if (!root)
				root = cmd_node;
			else if (current->type == PIPE)
				current->right = cmd_node;
			else
				current->left = cmd_node;
			current = cmd_node;
			// parssing_cmd(l_tokens,root, current);
			if (!l_tokens)
				break ;
		}
		else if (l_tokens->token->type == TOKEN_PIPE)
		{
			pipe_node = new_ast_node(PIPE, NULL);
			pipe_node->left = root;
			current = pipe_node;
			root = pipe_node;
			l_tokens = l_tokens->next;
		}
		else if (l_tokens->token->type == TOKEN_REDIR_IN
			|| l_tokens->token->type == TOKEN_REDIR_OUT
			|| l_tokens->token->type == TOKEN_APPEND)
		{
			if (!l_tokens->next || !l_tokens->next->token
				|| l_tokens->next->token->type != TOKEN_WORD)
			{
				ft_putstr_fd("Minishell:parse error near `\\n'\n", 2);
				return (NULL);
			}
			if (l_tokens->token->type == TOKEN_REDIR_IN)
			{
				if (root && root->type == CMD && root->value && is_builtin(root->value[0]))
				{
					l_tokens = l_tokens->next->next;
					root = get_args_redirection(root ,l_tokens);
					l_tokens = move_to_operator(l_tokens);
				continue;
					
				}
				else{
					
					
				red = new_ast_node(REDIR_IN, NULL);
				t_ast *file_node = new_ast_node(FILENAME,get_args_tokens(l_tokens->next));
					if (!file_node)
						return NULL;
		
					// Attach the file node as the left child of the redirection node
					red->left = file_node;	
				    red->left = root;
				}
			}
			else if (l_tokens->token->type == TOKEN_REDIR_OUT)
			{
				red = new_ast_node(REDIR_OUT, NULL);
				red->right = root;
			}
			else if (l_tokens->token->type == TOKEN_APPEND)
			{
				red = new_ast_node(APPEND, NULL);
				red->right = root;
			}
			red->right = root;
			root = red;
			current = root;
			l_tokens = l_tokens->next;
		}
		else
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(l_tokens->token->value, 2);
			ft_putstr_fd("'\n", 2);
			return (NULL);
		}
	}
	return (root);
}