/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:38:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/01 20:01:34 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_no_digit(long n, int base)
{
	int		no_digit;

	no_digit = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		no_digit++;
		n *= -1;
	}
	while (n)
	{
		n /= base;
		no_digit++;
	}
	return (no_digit);
}

char	*ft_itoa(long n, int base, char *radix)
{
	int		no_digit;
	int		index;
	char	*str;

	no_digit = get_no_digit(n, base);
	str = malloc(sizeof(char) * (no_digit + 1));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		*(str + 0) = '-';
		n *= -1;
	}
	index = no_digit - 1;
	if (n == 0)
		*(str + index) = '0';
	while (n > 0)
	{
		*(str + index--) = radix[n % base];
		n /= base;
	}
	*(str + no_digit) = '\0';
	return (str);
}
