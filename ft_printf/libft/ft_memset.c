/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:09:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/23 20:46:27 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// returns a void pointer
// Parameters:
// 1. ptr: pointer to the block of memory to fill
// 2. value: value to beset, passed as an int but the function fills the block
//    of memory using the unsigned char
// 3. number of bytes to be set to the value

// we cannot perform any pointer arithmetic on void pointer
// we cannot dereference void pointer

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	char	*location;

	location = ptr;
	while (num > 0)
	{
		*location = value;
		location++;
		num--;
	}
	return (ptr);
}
