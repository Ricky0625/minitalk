/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:32:47 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:21:05 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return a null terminated byte string, which is a duplicate of the string
// pointed to by str1

// return NULL if allocation failed

// logic copy the element in s1 to str and null-terminated it

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	size_t	index;

	len = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	index = 0;
	if (str == NULL)
		return (NULL);
	while (*s1)
	{
		*(str + index) = *(s1++);
		index++;
	}
	*(str + index) = '\0';
	return (str);
}
