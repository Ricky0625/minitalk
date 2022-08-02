/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:07:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 20:31:38 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// unsigned integer: nonnegative integer in the range 0 to 4294967295
// unsigned int vs size_t:
// https://stackoverflow.com/questions/131803/unsigned-int-vs-size-t

// s: the string from which to create the substring
// start: the start index of the substring in the string s.
// len: the maximum length of the substring, not including null

// return the substring, return null if allocation fails

#include "libft.h"

// get the malloc size (not including \0)
// to prevent the start index to be too absurd, so check if start greater or
// equal to length, return 0.
// if (start + len) greater than length, return (length - start). this is
// because if (start + len) > length, it means there's no enuf character
// to become a substring that has the size of len.
// for example: str = "Hello"; start at index 2 create a substr with length
// of 10.
// if there is no problem, meaning we can use the 'len' provided so just
// return len
static size_t	ft_get_size(char const *s, unsigned int start, size_t len)
{
	size_t	length;

	length = ft_strlen(s);
	if (start >= length)
		return (0);
	if ((start + len) > length)
		return (length - start);
	return (len);
}

// get the malloc size (not including \0) using ft_get_size
// malloc size is len + 1 (1 for \0)
// if malloc failed, return NULL
// while len is not 0 and char at (s + start) not \0, continue the loop
// then just insert the character from s to str
// null-terminated it at the end
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*str;

	if (!s)
		return (NULL);
	len = ft_get_size(s, start, len);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (len-- && *(s + start))
	{
		*(str + index) = *(s + start);
		index++;
		start++;
	}
	*(str + index) = '\0';
	return (str);
}
