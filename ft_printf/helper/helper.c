/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:07:14 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 14:05:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

// regular putchar but it returns the number of the printed character
int	ft_putchar(char c)
{
	return (write(1, &c, sizeof(char)));
}

// regular putstr but it returns the number of the printed characters
int	ft_putstr(char *str)
{
	int	out;

	if (str == NULL)
		return (0);
	out = 0;
	while (*str)
		out += ft_putchar(*(str++));
	return (out);
}
