/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:21:59 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:22:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// allocates and returns a new string, which is the result of the
// concatenation of s1 and s2

// s1: the prefix sting
// s2: the suffix string

// return the new string
// return null if the allocation fails

// char const * is a pointer to const char
// it's equivalent to const char *

// logic: copy each char of s1 to str first then s2, null terminated it

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	index;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (*s1)
		*(str + index++) = *s1++;
	while (*s2)
		*(str + index++) = *s2++;
	*(str + index) = '\0';
	return (str);
}
