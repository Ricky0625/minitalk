/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_adr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:45:42 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 14:52:48 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * print address in normal case
 * 
 * Process:
 * 1. print "0x"
 * 2. print leading '0' if pre_width larger than strlen
 * 3. Special case:
 * 	if the specification need precision, precision width is 0 && first 
 * 	character is 0, print nothing, return count instead.
 * 4. if the special case didn't occur, print the adr_str (Address in string)
**/
static int	print_adr_normal(char *adr_str, t_format *spec)
{
	int	count;

	count = 0;
	count += ft_putstr(ZERO_XL);
	count += print_space(spec->pre_width, '0');
	if (spec->precision && spec->pre_width == 0 && *adr_str == '0')
		return (count);
	count += ft_putstr(adr_str);
	return (count);
}

/**
 * check if left_align is needed,
 * if needed: print_adr_normal then print space
 * not needed: print space first then print_adr_normal
**/
static int	print_adr_spec(char *adr_str, t_format *spec)
{
	int	count;

	count = 0;
	if (spec->left_align)
	{
		count += print_adr_normal(adr_str, spec);
		count += print_space(spec->width, ' ');
	}
	else
	{
		count += print_space(spec->width, ' ');
		count += print_adr_normal(adr_str, spec);
	}
	return (count);
}

/**
 * print address
 * Process:
 * 1. convert the adr to string
 * 2. get strlen
 * 3. spec->width minus 2, because of the "0x"
 * 4. finalize specification
 * 5. print_adr_spec
**/
int	print_adr(unsigned long adr, t_format *spec)
{
	char	*adr_str;
	int		strlen;
	int		count;

	adr_str = ft_itoa_unsigned(adr, BASE_HEX, BASE_HEX_CL);
	strlen = ft_strlen(adr_str);
	count = 0;
	spec->width -= 2;
	finalize_spec(strlen, spec);
	count += print_adr_spec(adr_str, spec);
	free(adr_str);
	return (count);
}
