/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:56:15 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/30 17:54:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lst: the beginning of the list
// returns the last node of the list

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (lst != NULL)
	{
		current = lst;
		lst = lst->next;
	}
	return (current);
}
