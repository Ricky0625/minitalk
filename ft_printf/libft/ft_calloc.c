/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:32:14 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 14:44:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// calloc: Allocate and zero-initialize array

// allocates a block of memory for an array of num elements
// each of the element is size bytes long
// intialize all bits to zero

// if size is zero, return either be null pointer ot not, the returned pointer
// shall not be dereferenced in this case

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;
	size_t	total;

	total = num * size;
	if (num && size && (total / size) != num)
		return (NULL);
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
