/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:05:50 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 00:25:06 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list_token	*create_token_node(void *content)
{
	t_token			*token;
	t_list_token	*node;

	token = (t_token *)content;
	node = ft_lstnew(token);
	// free(token);
	return (node);
}

static t_list_token	*handle_token_node(t_token *token,
		t_list_token **token_list)
{
	t_list_token	*new_node;

	new_node = create_token_node(token);
	if (!new_node)
	{
		ft_lstclear(token_list, (void *)token_free);
		return (NULL);
	}
	ft_lstadd_back(token_list, new_node);
	return (new_node);
}

t_list_token	*tokenize_input(char *input, char **env)
{
	t_lexer			*lexer;
	t_list_token	*token_list;
	t_token			*current_token;

	lexer = lexer_init(input, env);
	if (!lexer)
		return (NULL);
	token_list = NULL;
	while (1)
	{
		current_token = lexer_get_next_token(lexer);
		if (!current_token)
			break ;
		if (!handle_token_node(current_token, &token_list))
			break ;
		if (current_token->type == TOKEN_EOF)
			break ;
	}
	lexer_free(lexer);
	return (token_list);
}
