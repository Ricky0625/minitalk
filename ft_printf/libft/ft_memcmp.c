/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:02:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/25 19:44:56 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memcmp: http://surl.li/cbdyc

// compare using unsigned char
// unlike strcmp, the function does not stop comparing when encounter \0

// index for accessing the character of each string
// index < num, only access until this far
// while looping, check if the current character of s1 not equal s2
// if not equal, directly return the difference between them
// if equal, keep the loop run. if the loop ends, meaning all char matches

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			index;
	unsigned char	*a;
	unsigned char	*b;

	index = 0;
	a = (unsigned char *)ptr1;
	b = (unsigned char *)ptr2;
	while (index < num)
	{
		if (a[index] != b[index])
			return (a[index] - b[index]);
		index++;
	}
	return (0);
}
