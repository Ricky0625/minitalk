/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:00:03 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 15:11:46 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * this function print the string but will check if the string needs to be
 * left-aligned or not
 * if left-align flag
 * 		a. existed, print the string first then the trailing spaces
 * 		b. not existed, leading space will get printed first then the str
**/
static int	print_left_str(char *str, t_format *spec)
{
	int	strlen;
	int	left_align;
	int	space;
	int	count;

	strlen = ft_strlen(str);
	left_align = spec->left_align;
	space = spec->width - strlen;
	count = 0;
	if (left_align)
	{
		count += ft_putstr(str);
		count += print_space(space, space_or_zero(spec));
	}
	else
	{
		count += print_space(space, space_or_zero(spec));
		count += ft_putstr(str);
	}
	return (count);
}

/**
 * print out the string
 * if width > strlen, meaning left-align, zero-padding flag can be used
 * so use print_left_str to print the string with specification
 * if widtth <= strlen, just putstr normally
**/
static int	print_out_str(char *str, int strlen, t_format *spec)
{
	int	width;
	int	count;

	width = spec->width;
	count = 0;
	if (width > strlen)
		count += print_left_str(str, spec);
	else
		count += ft_putstr(str);
	return (count);
}

/**
 * print string
 * Process
 * 1. check if the str is null. if yes, set output str as "(null)"
 * 2. If precision is set,
 * 		a. create a substr, with the length of pre_width
 * 		b. print the substr
 * 3. If precision is not set, print out the string normally
**/
int	print_str(char *str, t_format *spec)
{
	char	*prc_str;
	int		prc_len;
	int		count;

	if (str == NULL)
		str = STR_NULL;
	prc_len = ft_strlen(str);
	count = 0;
	if (spec->precision)
	{
		prc_str = ft_substr(str, 0, spec->pre_width);
		prc_len = ft_strlen(prc_str);
		count = print_out_str(prc_str, prc_len, spec);
		free(prc_str);
	}
	else
		count = print_out_str(str, prc_len, spec);
	return (count);
}
