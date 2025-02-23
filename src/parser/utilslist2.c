/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslist2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaada <rjaada@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:39:21 by rjaada            #+#    #+#             */
/*   Updated: 2025/02/23 21:39:40 by rjaada           ###   ########.fr       */
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
