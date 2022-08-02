/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:12:13 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 14:03:31 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

// check if the character is flag
static int	isflag(char c)
{
	return (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#');
}

/**
 * Iterate through the format string, as long as it's one of the flag
 * 
 * When found flag, modify the spec (conversion specification)
 * This function when also deal with the conflict between flags (man printf)
 * 1. '-' overrides '0'
 * 2. '+' overrides space
**/
char	*read_flags(t_format *spec, char *str)
{
	while (*str && isflag(*str))
	{
		if (*str == '-')
		{
			spec->left_align = 1;
			spec->zero_padd = 0;
		}
		if (*str == '0' && spec->left_align == 0)
			spec->zero_padd = 1;
		if (*str == '+')
		{
			spec->plus_sign = 1;
			spec->inv_sign = 0;
		}
		if (*str == ' ' && spec->plus_sign == 0)
			spec->inv_sign = 1;
		if (*str == '#')
			spec->hashtag = 1;
		str++;
	}
	return (str);
}

/**
 * Previously this function is to return the digit of numbers
 * example: 234. 3 digit
 * but, this will not work when the width or precision is something like '05'
 * so, instead of getting the digit of a number, count the number of digit
 * in the string
**/
static int	get_num_digit(char *str)
{
	int	count;

	count = 0;
	while (ft_isdigit(*str))
	{
		count++;
		str++;
	}
	return (count);
}

/**
 * Process of retreiving the width and precision
 * 
 * 1. get the width
 * 2. detect if there is a dot
 * 3. get the precision
 * 
 * 
**/
char	*read_width_precision(t_format *spec, char *str)
{
	if (ft_isdigit(*str))
	{
		spec->width = ft_atoi(str);
		str += get_num_digit(str);
	}
	if (*str == '.')
	{
		spec->precision = 1;
		str++;
	}
	if (ft_isdigit(*str))
	{
		spec->pre_width = ft_atoi(str);
		str += get_num_digit(str);
	}
	return (str);
}

// get the conversion type
char	*read_type(t_format *spec, char *str)
{
	spec->type = *str;
	str++;
	return (str);
}
