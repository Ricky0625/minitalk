/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:03:06 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 10:49:27 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lst: the address of a pointer to the first link of a list
// new: the address of a pointer to the node to be added to the list

// add the node 'new' at the end of the list

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return ;
}
