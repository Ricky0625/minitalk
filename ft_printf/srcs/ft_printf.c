/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:17:23 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 16:04:54 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * The process of reading the arguments
 * 
 * The syntax of the conversion specification strictly follow this:
 * %[flags][width][.precision][conversion type]
 * So, the process will be:
 * 
 * 1. Read flags (+,-,space,#,0). Sequence doesn't matter for flags.
 * 2. Read width & precision (width.precision)
 * 3. Read conversion type (cspdiuxX%)
 * 
 * Note: The address of 'str' will be modified along the way.
**/
static char	*read_args(t_format *spec, char *str)
{
	str = read_flags(spec, str);
	str = read_width_precision(spec, str);
	str = read_type(spec, str);
	return (str);
}

// Initialize all the struct members to 0
static void	init_spec(t_format *spec)
{
	spec->left_align = 0;
	spec->zero_padd = 0;
	spec->inv_sign = 0;
	spec->plus_sign = 0;
	spec->hashtag = 0;
	spec->width = 0;
	spec->precision = 0;
	spec->pre_width = 0;
	spec->type = 0;
}

/**
 * This function is just for debugging
 * Uncomment this function, include stdio.h and uncomment the function
 * definition in header file to use it
 * Will print all the details of the struct
**/
/**
void	print_tformat(t_format *spec)
{
	printf("\nleft align:\t%d\n", spec->left_align);
	printf("zero padding:\t%d\n", spec->zero_padd);
	printf("invisible sign:\t%d\n", spec->inv_sign);
	printf("plus sign:\t%d\n", spec->plus_sign);
	printf("hashtag:\t%d\n", spec->hashtag);
	printf("width:\t\t%d\n", spec->width);
	printf("precision:\t%d\n", spec->precision);
	printf("preci width:\t%d\n", spec->pre_width);
	printf("conver type:\t%c\n", spec->type);
	printf("######################################\n");
}
**/

/**
 * Process the format str
 * 
 * 1. Iterate through the str
 * 2. Check if there is a '%'.
 * 		a. Yes, meaning the output should follow a set of specification
 * 		b. No, just a normal character, ft_putchar the character
 * 2a. (cont')
 * 	i.		initialize spec before process to read args
 * 	ii.		read_args (flags, width, precision, conversion type)
 * 	iii.	check if the conversion type is 0 or not, if yes, meaning invalid
 * 			conversion type, just return 0
 *  iv.		convert the args into the requested format
**/
static int	process_str(char *str, t_format *spec, va_list args)
{
	int	out;

	out = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			init_spec(spec);
			str = read_args(spec, str);
			if (spec->type == 0)
				return (0);
			out += convert_args(spec, args);
		}
		else
		{
			out += ft_putchar(*str);
			str++;
		}
	}
	return (out);
}

/**
 * ft_printf (driver function)
 * 
 * 1. initialize the va_list using va_start
 * 2. process the format string
 * 3. free va_list using va_end
 * 
 * Use a struct to store all the conversion specification
 * Check includes/ft_printf.h for the details of the struct
**/
int	ft_printf(const char *format, ...)
{
	int			out;
	char		*str;
	t_format	spec;
	va_list		args;

	str = (char *)format;
	if (format == NULL)
		return (0);
	out = 0;
	va_start(args, format);
	out = process_str(str, &spec, args);
	va_end(args);
	return (out);
}
