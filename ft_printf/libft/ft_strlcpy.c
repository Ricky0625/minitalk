/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:07:11 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/24 20:29:50 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// contents of src are copied into dst in both strcpy and strlcpy
// the difference is that strlcpy only copy size of characters
// the value returned is the size of src. the value returned is always the size
// of src regardless of how many characters are copied.
// the function assumed that src is null terminated
// copy up to size - 1, because need to reserve one space for null terminator
// need manually null terminated the string before return

// if size == 0, supposingly should be size <= 0, but since size is size_t
// meaning it's not possible to have negative value, the compiler will warn
// us if we do that, so we just check if size is 0
// if size is 0, meaning nothing to copy, so just return the length of src

// --size is because, we need to reserve a space for \0, so during evaluation,
// we want it to evaluates to the new value (size - 1)

// as long as the src is not \0 and the size to copy is not 0, continue loop
// once one of the condition could not be fulfilled, exit loop
// manually append \0 afterward

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	index;

	len = ft_strlen(src);
	index = 0;
	if (size == 0)
		return (len);
	while (src[index] && --size)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (len);
}
