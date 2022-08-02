/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:53:44 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:25:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return pointer to the last occurrence of ch in str
// if not found, return NULL

// similar like strchr, the difference is that, it does not break out of the
// loop once it encounter the first occurrence, it keeps on searching and
// updating the occurrence until reaches \0

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	char	*occurrence;
	char	target;

	occurrence = NULL;
	target = ch;
	if (target == '\0')
		return (ft_strchr(str, ch));
	while (*str)
	{
		if (*str == target)
			occurrence = (char *)str;
		str++;
	}
	return (occurrence);
}
