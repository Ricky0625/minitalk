/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:19:19 by wricky-t          #+#    #+#             */
/*   Updated: 2022/07/30 19:33:59 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>

# define ZERO_XL "0x"
# define ZERO_XU "0X"
# define BASE_BIN 2
# define BASE_DEC 10
# define BASE_DEC_CH "0123456789"
# define BASE_HEX 16
# define BASE_HEX_CL "0123456789abcdef"
# define BASE_HEX_CU "0123456789ABCDEF"
# define STR_NULL "(null)"

/* ***************************
Flags, Width, Precision, Type
left_align	: -
zero_padd	: 0
inv_sign	: space
plus_sign	: +
hashtag		: #
width		: width size
precision	: .
pre_width	: precision width
type		: csuidxX%

Format Specification Format
%[flags][width][.precision]type
****************************** */

typedef struct s_format
{
	int	left_align;
	int	zero_padd;
	int	inv_sign;
	int	plus_sign;
	int	hashtag;
	int	width;
	int	precision;
	int	pre_width;
	int	type;
}	t_format;

// main
int		ft_printf(const char *format, ...);

// helper functions
int		ft_putchar(char c);
int		ft_putstr(char *str);

// arguments helper
char	*read_flags(t_format *spec, char *str);
char	*read_width_precision(t_format *spec, char *str);
char	*read_type(t_format *spec, char *str);

// conversion helper
int		convert_args(t_format *spec, va_list args);

// print helper
char	space_or_zero(t_format *spec);
int		print_space(int qty, char c);
void	finalize_spec(int strlen, t_format *spec);
int		print_char(char c, t_format *spec);
int		print_str(char *str, t_format *spec);
int		print_adr(unsigned long adr, t_format *spec);
int		print_hex(unsigned int n, t_format *spec);
int		print_unsigned(unsigned int n, t_format *spec);
int		print_num(int n, t_format *spec);

// testing helper
void	print_tformat(t_format *spec);
#endif