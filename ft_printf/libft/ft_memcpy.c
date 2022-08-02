/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:59:53 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:35:24 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dst: pointer to destination
// src: pointer to source
// num: number of bytes to copy

// function does not check for any terminating null character in src
// ↑ difference between strcpy. when strcpy encounters a NULL, it stops
// memcpy does not

// use num for iteration, while num is greater than 0
// value at cdst equal to value at csrc
// increment cdst and csrc, decrement num
// lastly return dst
// allowed overlay, idea is to copy forward
// memcpy blindly copies forward

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	char		*cdst;
	const char	*csrc;

	if (src == NULL && dst == NULL)
		return (NULL);
	cdst = dst;
	csrc = src;
	while (num > 0)
	{
		*cdst = *csrc;
		cdst++;
		csrc++;
		num--;
	}
	return (dst);
}
