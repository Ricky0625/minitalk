/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:53:21 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 14:28:44 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

// substitue space to '0' if zero_padding flag is enabled
char	space_or_zero(t_format *spec)
{
	if (spec->zero_padd)
		return ('0');
	return (' ');
}

// print leading/trailing spaces
int	print_space(int qty, char c)
{
	int	count;

	count = 0;
	while (qty--)
		count += ft_putchar(c);
	return (count);
}

/**
 * use to finalize the length of precision
 * Cases:
 * 1. Precision width > width
 * precision width overwrites width so width = 0
 * if width = 0, then left-align should set to 0 as well
 * 
 * 2. Width > Precision width
 * the length of the hashtag flag(0x/0X) is calculated tgt with width
 * so check if hashtag exists, width -2
 * when width greater than precision width, width will not overwrites
 * precision width, but precision width will affects the width
 * so width need to minus pre_width
 * 
 * 3. General cases/rules
 * if precision is set, zero padding flag is ignored
 * if precision is set, the actual width for precision that needs to
 * be printed out is pre_width - stren.
**/
void	finalize_precision(int strlen, t_format *spec)
{
	if (spec->pre_width > spec->width)
	{
		spec->width = 0;
		spec->left_align = 0;
	}
	if (spec->width > spec->pre_width)
	{
		if (spec->hashtag)
			spec->width -= 2;
		spec->width -= spec->pre_width;
	}
	spec->zero_padd = 0;
	if (spec->pre_width != 0)
		spec->pre_width -= strlen;
}

/**
 * this function is use to finalize the specification
 * Cases:
 * 1. strlen >= width OR width == pre_width
 * no point of having width, so set it to 0
 * 
 * 2. strlen >= precision width
 * no point of having precision width, set precision related info to 0
 * precision doesn't work with zero padding flag, so set to 0
 * 
 * 3. if precision is set (1 = has precision, 0 = no precision)
 * finailize precision
 * 
 * 4. if there is no precision, and width > strlen
 * width minus 2 if hashtag exists
 * width = width - strlen
**/
void	finalize_spec(int strlen, t_format *spec)
{
	if ((strlen >= spec->width) || spec->width == spec->pre_width)
		spec->width = 0;
	if (spec->precision == 1 && strlen >= spec->pre_width)
	{
		if (spec->pre_width != 0)
		{
			spec->precision = 0;
			spec->pre_width = 0;
		}
		spec->zero_padd = 0;
	}
	if (spec->precision)
		finalize_precision(strlen, spec);
	if (!spec->precision && spec->width > strlen)
	{
		if (spec->hashtag)
			spec->width -= 2;
		spec->width -= strlen;
	}
}
