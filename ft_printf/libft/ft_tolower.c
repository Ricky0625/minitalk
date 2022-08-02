/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:30:58 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:29:42 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check if ch is uppercase character
static int	ft_isupper(int ch)
{
	return (ch >= 'A' && ch <= 'Z');
}

// if the character is uppercase, turn it into lowercase
int	ft_tolower(int ch)
{
	if (ft_isupper(ch))
		return (ch + 32);
	return (ch);
}
