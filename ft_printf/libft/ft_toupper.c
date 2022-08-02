/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:42:12 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 17:30:09 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// check if ch is lowercase
static int	ft_islower(int ch)
{
	return (ch >= 'a' && ch <= 'z');
}

// if ch is lowercase, turn it into uppercase
int	ft_toupper(int ch)
{
	if (ft_islower(ch))
		return (ch - 32);
	return (ch);
}
