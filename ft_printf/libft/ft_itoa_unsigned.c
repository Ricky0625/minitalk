/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_old.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:17:00 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/01 20:04:19 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_no_digit(unsigned long n, int base)
{
	int		no_digit;

	no_digit = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= base;
		no_digit++;
	}
	return (no_digit);
}

char	*ft_itoa_unsigned(unsigned long n, int base, char *radix)
{
	int		no_digit;
	int		index;
	char	*str;

	no_digit = get_no_digit(n, base);
	str = malloc(sizeof(char) * (no_digit + 1));
	if (str == NULL)
		return (NULL);
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
