/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:08:14 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 15:55:23 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * finalize spec but with one super specific case
 * 
 * if n == 0, precision is set and it's 0, width is 1,
 * don't clear width, but clear zero_padd only
**/
static void	finalize_unsigned_spec(int n, int len, t_format *spec)
{
	if (n == 0 && spec->precision
		&& spec->pre_width == 0 && spec->width == 1)
		spec->zero_padd = 0;
	else
		finalize_spec(len, spec);
}

/**
 * print unsigned int in normal case
 * 
 * 1. print '0' if precision is set
 * 2. print '0' if zero_padd is set (work run if precision is set)
 * 3. Special case:
 * 	if the specification need precision, precision width is 0 && first 
 * 	character is 0, print nothing, return count instead.
 * 4. if not special case, putstr the string
**/
static int	print_unint_normal(char *un_str, t_format *spec)
{
	int	count;

	count = 0;
	count += print_space(spec->pre_width, '0');
	if (spec->zero_padd)
		count += print_space(spec->width, '0');
	if (spec->precision && spec->pre_width == 0 && *un_str == '0')
		return (count);
	count += ft_putstr(un_str);
	return (count);
}

// print str in left-align if the flag is set
static int	print_unint_spec(char *un_str, t_format *spec)
{
	int	count;

	count = 0;
	if (spec->left_align)
	{
		count += print_unint_normal(un_str, spec);
		count += print_space(spec->width, space_or_zero(spec));
	}
	else
	{
		if (spec->zero_padd)
			count += print_unint_normal(un_str, spec);
		else
		{
			count += print_space(spec->width, ' ');
			count += print_unint_normal(un_str, spec);
		}
	}
	return (count);
}

/**
 * Process:
 * 1. convert n to string
 * 2. finalize spec
 * 3. print the string
**/
int	print_unsigned(unsigned int n, t_format *spec)
{
	char	*un_str;
	int		strlen;
	int		count;

	un_str = ft_itoa(n, BASE_DEC, BASE_DEC_CH);
	strlen = ft_strlen(un_str);
	count = 0;
	finalize_unsigned_spec(n, strlen, spec);
	count += print_unint_spec(un_str, spec);
	free(un_str);
	return (count);
}
