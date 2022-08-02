/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:43:01 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/30 18:58:47 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * finalize spec but with additional condition
 * if n >=0, and either plus_sign flag / invisible plus sign flag exists
 * width--. because reserve one space for '+' / ' '
**/
static void	finalize_num_spec(int n, int len, t_format *spec)
{
	if (n >= 0 && (spec->plus_sign || spec->inv_sign))
		spec->width--;
	if (n == 0 && spec->precision
		&& spec->pre_width == 0 && spec->width == 1)
		spec->zero_padd = 0;
	else
		finalize_spec(len, spec);
}

/**
 * print the '+' or ' ' sign for positive number
 * print the  '-' sign for negative number
**/
static int	print_sign(int n, t_format *spec)
{
	int	count;

	count = 0;
	if (n >= 0)
	{
		if (spec->inv_sign)
			count += ft_putchar(' ');
		if (spec->plus_sign)
			count += ft_putchar('+');
	}
	else if (n < 0)
		count += ft_putchar('-');
	return (count);
}

/**
 * print out the number in string format (normal case)
 * 
 * Process:
 * 1. print the negative/positive sign
 * 2. print the precision width
 * 3. if zero padding exists, print the space
 * 4. print the string (the number in string format)
**/
static int	print_num_normal(int n, char *num_str, t_format *spec)
{
	int	count;

	count = 0;
	count += print_sign(n, spec);
	count += print_space(spec->pre_width, '0');
	if (spec->zero_padd)
		count += print_space(spec->width, '0');
	if (spec->precision && spec->pre_width == 0 && *num_str == '0')
		return (count);
	count += ft_putstr(num_str);
	return (count);
}

// used to print the string in left-align if needed
static int	print_num_spec(int n, char *num_str, t_format *spec)
{
	int	count;

	count = 0;
	if (spec->left_align)
	{
		count += print_num_normal(n, num_str, spec);
		count += print_space(spec->width, space_or_zero(spec));
	}
	else
	{
		if (spec->zero_padd)
			count += print_num_normal(n, num_str, spec);
		else
		{
			count += print_space(spec->width, ' ');
			count += print_num_normal(n, num_str, spec);
		}
	}
	return (count);
}

/**
 * Process:
 * 1. convert the number to string (ft_itoa)
 * 2. if n is less than 0 (ie: -456, -2346, -1),
 * 		a. use substring to create a substring that has no '-' sign
 * 		b. width--. bcos we need reserve one space for negative sign
 * 		c. strlen--. bcos previously '-' is counted in strlen
 * 3. finalize the specification
 * 4. print the str
**/
int	print_num(int n, t_format *spec)
{
	char	*num_str;
	char	*temp;
	int		strlen;
	int		count;

	num_str = ft_itoa(n, BASE_DEC, BASE_DEC_CH);
	strlen = ft_strlen(num_str);
	if (n < 0)
	{
		temp = num_str;
		num_str = ft_substr(num_str, 1, strlen - 1);
		free(temp);
		spec->width--;
		strlen--;
	}
	count = 0;
	finalize_num_spec(n, strlen, spec);
	count += print_num_spec(n, num_str, spec);
	free(num_str);
	return (count);
}
