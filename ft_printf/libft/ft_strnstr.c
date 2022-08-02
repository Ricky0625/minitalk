/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 09:04:06 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 10:49:43 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// locate the first occurrence of the null-terminated string 'needle' in the
// null-terminated string 'haystack'
// characters after \0 character are not searched

// return values:
// if 'needle' is an empty string, 'haystack' is returned
// if 'needle' occurs nowhere in 'haystack', NULL is returned
// if 'needle' can be found in 'haystack', return a pointer to the first
// character of the first occurrence of 'needle'

// an empty string has a single element, the null character, \0

// needle: substring; haystack: the string

// logic:
// first check if needle is an empty string, if yes, return haystack
// if needle is not an empty string, we begin to search
// while haystack at index h_id not \0 and h_id less than len we continue
// n_id = 0 is to reset needle's index if the search failed

// h_id + n_id for traversing haystack, this way if the needle is found, we
// can trace back the first character of the first occurrence of needle

// h_id + n_id < len for prevent the function go beyond the search length

// the inner loop will stop if the current char at hay and needle not equal
// or h_id + n_id >= len (meaning exceed search length)
// the outer loop will stop if the current char at hay is \0 or h_id go
// beyond the search length

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_id;
	size_t	n_id;

	if (*needle == '\0')
		return ((char *)haystack);
	h_id = 0;
	while (haystack[h_id] && h_id < len)
	{
		n_id = 0;
		while (haystack[h_id + n_id] == needle[n_id] && (h_id + n_id) < len)
		{
			if (needle[n_id + 1] == '\0')
				return ((char *)(haystack + h_id));
			n_id++;
		}
		h_id++;
	}
	return (NULL);
}
