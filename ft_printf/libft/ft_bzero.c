/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:51:53 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:10:11 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// s: points to a buffer that zeros are copied into
// n: is the number of zero be copied into the buffer

// write n zeroed bytes to the string s
// if n is zero, bzero() does nothing

// implementing using memset. for memset, if n = 0, just return s.

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
