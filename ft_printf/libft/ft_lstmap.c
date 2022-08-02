/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:39:08 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 14:45:26 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// iterates lst, apply function f on the 'content' of each node
// create a new list after each successive applications of function 'f'
// the del function is used to delete the content of a node "if needed"

// - apply f on each node's content
// if successfully apply f on each node, then return
// else delete the whole list using del

// (*f) indicates it is a function pointer
// void *(*f): a function pointer that returns a void pointer
// void *(*f)(void *): this function pointer accepts a void pointer

// firstly, try to create a new node using lstnew.
// lstnew will return null if malloc fail. in that case, we clear the lst and
// return null
// if lstnew able to create a new node, we apply f on the rest of the node
// but before that we have to shift the pointer to lst to the next node
// also to set newlist to point to newnode. previously is null
// then use a loop to traverse through the lst, for each node, we try to
// create a new node based on the result of the f applied on the node
// check if the newnode is created, if not, we clear the lst and break loop
// because there's error
// if new node can be created, shift the pointer to lst to the next node
// add the newly created node to the new list

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;

	if (lst == NULL)
		return (NULL);
	newlist = NULL;
	newnode = ft_lstnew(f(lst->content));
	if (newnode == NULL)
		return (NULL);
	newlist = newnode;
	lst = lst->next;
	while (lst)
	{
		newnode = ft_lstnew(f(lst->content));
		if (newnode == NULL)
		{
			ft_lstdelone(lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&newlist, newnode);
	}
	return (newlist);
}
