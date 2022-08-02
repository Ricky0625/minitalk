/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:46:31 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/22 12:10:30 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * Midway checkpoint for getting the output
 * 
 * Re-route to the respective function based on the conversion type
**/
int	convert_args(t_format *spec, va_list args)
{
	char	type;

	type = spec->type;
	if (type == 'c')
		return (print_char(va_arg(args, int), spec));
	else if (type == 's')
		return (print_str(va_arg(args, char *), spec));
	else if (type == 'p')
		return (print_adr(va_arg(args, unsigned long), spec));
	else if (type == 'd' || type == 'i')
		return (print_num(va_arg(args, int), spec));
	else if (type == 'u')
		return (print_unsigned(va_arg(args, unsigned int), spec));
	else if (type == 'x' || type == 'X')
		return (print_hex(va_arg(args, unsigned int), spec));
	else if (type == '%')
		return (print_char('%', spec));
	return (0);
}
