/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:35:54 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/30 16:24:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lst: the beginning of the list
// return the length of the list

// firstly, check whether lst is null, if true, return 0.
// while ptr is not null, increment len, update ptr to ptr->next

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*ptr;
	int		len;

	if (lst == NULL)
		return (0);
	ptr = lst;
	len = 0;
	while (ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}
