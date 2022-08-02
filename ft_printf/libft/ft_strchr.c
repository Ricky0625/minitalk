/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:15:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/05/24 15:35:41 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// locates the first occurrence of ch in the str
// \0 considers as part of the str, therefor if ch is \0, then locate \0
// this function will assume that the str is already null terminated
// if there is no occurrence, return NULL

// in order to let the while loop keep iterating, *str must not be \0 AND *str
// must not be the target character. if these conditions are fulfilled,
// increment str so that we can traverse the string
// if the first condition is not fulfilled, meaning, we reach the \0. at this
// point, the target character is either the \0 or char that is not in the str.
// if the second condition is not fulfilled, it means we have the target char
// to validate that, we will check if *str == target, if yes, then occurrence =
// str (the address of the character that we are pointing now)
// if cannot pass the if statement, meaning str does not have ch, return NULL

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	char	*occurrence;
	char	target;

	occurrence = NULL;
	target = ch;
	while (*str && *str != target)
	{
		str++;
	}
	if (*str == target)
		occurrence = (char *)str;
	return (occurrence);
}
