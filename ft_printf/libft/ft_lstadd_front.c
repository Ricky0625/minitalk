/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:50:56 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/30 17:54:22 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lst: address of a pointer to the first link of the list
// new: address of a pointer to the node to be added to the list

// adds the node 'new' at the beginning of the list

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
