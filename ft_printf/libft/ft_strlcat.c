/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:34:38 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/31 11:47:24 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// concatenate characters from src to dest and null terminating the string
// as much of src is copied into dest as there is space for

// parameters:
// size: size of dst + 1 (nul-terminator)
// dst: dest string. src: source string

// return the LENGTH OF THE CONCATENATED STRING, WHETHER OR NOT IT WAS POSSIBLE
// TO COPY IT ALL
// if all src was concatenated to dst, the return value will be less than size
// if dst is not nul-terminated, then strlcat will consider dst to be size in
// length and return size plus the length of src

// my understanding on size is the expected length of the resulting string

// first, check size is <= length of dst. if true, then return slen + size
// size cannot < dlen. if we insist to concat src & dst so that its' len
// can be size, meaning, some data in dst will be missing.
// size cannot = dlen, because we have to reserve one space for the null
// if size >= dlen, meaning we can have some character from src to be
// concatenated to dst.
// while *src not null and (dlen + 1) < size, we concat
// dlen + 1, we have to consider the null terminator as well
// lastly return dlen + slen, not including null.

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	append_at;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (slen + size);
	append_at = dlen;
	while (*src && (dlen + 1) < size)
	{
		dst[append_at] = *src;
		append_at++;
		src++;
		size--;
	}
	dst[append_at] = '\0';
	return (dlen + slen);
}
