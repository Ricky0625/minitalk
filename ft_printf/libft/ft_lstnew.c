/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:23:34 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/07 13:43:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// create a new node, initialize the node's content with content (parameter)
// intialize the next(the address to next node) as NULL
// return the node (address of the node)

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
