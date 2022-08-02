/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:31:42 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:26:52 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// locate character in block of memory

// search within the first num bytes of the block pointed by ptr for the first
// occurrence of value

// ptr: pointer to the block of memory where the search is performed
// value: value to be located. passed in as int, but the function will use it
// as unsigned char conversion of this value
// num: number of bytes to be analyzed

// return the first occurrence of value in the block of memory pointed by ptr
// if not found, return null pointer

// reference: https://m.cplusplus.com/reference/cstring/memchr/

// logic: while there's still number of bytes to search, check if the value at
// current location is the target value. if yes, set occurrence point to the
// current location and break the loop. then just return occurrence (pointer)
// if num == 0, meaning we ady search thru the bytes and there's no occurrence
// hence return NULL

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	target;
	unsigned char	*cptr;
	unsigned char	*occurrence;

	cptr = (unsigned char *)ptr;
	target = value;
	occurrence = NULL;
	while (num)
	{
		if (*cptr == target)
		{
			occurrence = cptr;
			break ;
		}
		cptr++;
		num--;
	}
	return (occurrence);
}
