/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 10:42:28 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 15:57:33 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * finalize spec but with one super specific case
 * 
 * if n == 0, precision is set and it's 0, width is 1,
 * don't clear width, but clear zero_padd only
**/
static void	finalize_hex_spec(int n, int len, t_format *spec)
{
	if (n == 0 && spec->precision
		&& spec->pre_width == 0 && spec->width == 1)
		spec->zero_padd = 0;
	else
		finalize_spec(len, spec);
}

/**
 * to print the spec and string in sequence (normal case)
 * zerox -> precision -> width -> hexa_str
**/
static int	print_hex_normal(char *hex_str, char *zerox, t_format *spec)
{
	int	count;

	count = 0;
	if (spec->hashtag)
		count += ft_putstr(zerox);
	count += print_space(spec->pre_width, '0');
	if (spec->zero_padd)
		count += print_space(spec->width, '0');
	if (spec->precision && spec->pre_width == 0 && *hex_str == '0')
		return (count);
	count += ft_putstr(hex_str);
	return (count);
}

/**
 * use to print hex_str with the spec
 * especially made for left align
**/
static int	print_hex_spec(char *hex_str, char *zerox, t_format *spec)
{
	int	count;

	count = 0;
	if (spec->left_align)
	{
		count += print_hex_normal(hex_str, zerox, spec);
		count += print_space(spec->width, space_or_zero(spec));
	}
	else
	{
		if (spec->zero_padd)
			count += print_hex_normal(hex_str, zerox, spec);
		else
		{
			count += print_space(spec->width, ' ');
			count += print_hex_normal(hex_str, zerox, spec);
		}
	}
	return (count);
}

/**
 * handles x and X
 * if X, then set charset and zerox to uppercase version
 * if n = 0, hashtag flag ignored
 * 
 * Process:
 * decide charset & zerox
 * turn the value to string (ft_itoa)
 * finalize specification (width, zero_padd, precision)
 * print the hexadecimal string
 * return the number of processed characters
**/
int	print_hex(unsigned int n, t_format *spec)
{
	char	*charset;
	char	*zerox;
	char	*hex_str;
	int		strlen;
	int		count;

	charset = BASE_HEX_CL;
	zerox = ZERO_XL;
	if (spec->type == 'X')
	{
		charset = BASE_HEX_CU;
		zerox = ZERO_XU;
	}
	if (n == 0)
		spec->hashtag = 0;
	hex_str = ft_itoa(n, BASE_HEX, charset);
	strlen = ft_strlen(hex_str);
	count = 0;
	finalize_hex_spec(n, strlen, spec);
	count += print_hex_spec(hex_str, zerox, spec);
	free(hex_str);
	return (count);
}
