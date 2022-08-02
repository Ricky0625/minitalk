/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:16:20 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 11:59:18 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strncmp: shorturl.at/oprzT

// Compare characters of two strings
// start by comparing the first character of each string
// if equal, continue to the next pair until:
// 1. the characters of the following pair differ
// 2. until null terminator (either one)
// 3. until num of characters is compared
// the loop stops whichever happens

// return value:
// < 0: str1 < str2
// 0: both string are identical
// > 0: str1 > str2
// man stated that the comparison is done using unsigned char
// so need to typecast it

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	while (num && (*str1 || *str2))
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		num--;
		str1++;
		str2++;
	}
	return (0);
}
