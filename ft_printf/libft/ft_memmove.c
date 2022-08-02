/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:01:55 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:37:33 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// copies len bytes of src to dst, allows copying between objects that might
// overlay as if src is first copied into a temporary array (theoretically)

// reference: http://surl.li/cbccj (discussion on the implementation)

// instead of copy forward →, we try copy backward ←
// handle the part that might overlay first

// dst + len - 1: because we are shifting the position of pointer, so need -1
// len starts counting from 1

// if the address of src if greater than dst, it's actually copies forward
// which can use memcpy (also copies forward)

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;

	if (src == NULL && dst == NULL)
		return (NULL);
	if (src > dst)
	{
		ft_memcpy(dst, src, len);
		return (dst);
	}
	while (len > 0)
	{
		cdst = dst + len - 1;
		csrc = src + len - 1;
		*cdst = *csrc;
		len--;
	}
	return (dst);
}
