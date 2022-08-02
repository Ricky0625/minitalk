/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:05:08 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 14:56:28 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * check if left align
 * 		a. exists. putchar first then trailing spaces
 * 		b. not exists. leading spaces first then putchar
**/
static int	print_left_char(char c, t_format *spec)
{
	int	left_align;
	int	space;
	int	count;

	left_align = spec->left_align;
	space = spec->width - 1;
	count = 0;
	if (left_align)
	{
		count += ft_putchar(c);
		count += print_space(space, space_or_zero(spec));
	}
	else
	{
		count += print_space(space, space_or_zero(spec));
		count += ft_putchar(c);
	}
	return (count);
}

/**
 * print a character
 * only works with [width] && [left-align if width > 1]
**/
int	print_char(char c, t_format *spec)
{
	int	width;
	int	count;

	width = spec->width;
	count = 0;
	if (width > 1)
		count += print_left_char(c, spec);
	else
		count += ft_putchar(c);
	return (count);
}
