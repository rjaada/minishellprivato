/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 20:18:38 by kmoundir          #+#    #+#             */
/*   Updated: 2025/02/18 15:41:43 by rjaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list_token **lst, t_list_token *new)
{
	t_list_token	*list_tmp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	list_tmp = *lst;
	while (list_tmp->next)
	{
		list_tmp = list_tmp->next;
	}
	list_tmp->next = new;
}

void	ft_lstadd_front(t_list_token **lst, t_list_token *new)
{
	new->next = *lst;
	*lst = new;
}
// we should fix this function
void	ft_lstclear(t_list_token **lst, void (*del)(void *))
{
	t_list_token	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->token);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list_token *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->token);
	free(lst);
}

void	ft_lstiter(t_list_token *lst, void (*f)(void *))
{
	t_list_token	*temp;

	if (!lst || !f)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->token);
		temp = temp->next;
	}
}

t_list_token	*ft_lstnew(void *content)
{
	t_list_token	*new_node;

	new_node = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new_node)
		return (NULL);
	new_node->token = content;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstsize(t_list_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_list_token	*ft_lstlast(t_list_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

// **************************
static t_list_token	*ft_clear_if_error(t_list_token **new_list,
		void (*del)(void *))
{
	ft_lstclear(new_list, del);
	return (NULL);
}

t_list_token	*ft_lstmap(t_list_token *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list_token	*new_list;
	t_list_token	*node;
	void			*content_map;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content_map = f(lst->token);
		if (!content_map)
			return (ft_clear_if_error(&new_list, del));
		node = ft_lstnew(content_map);
		if (!node)
		{
			del(content_map);
			return (ft_clear_if_error(&new_list, del));
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
// **************************