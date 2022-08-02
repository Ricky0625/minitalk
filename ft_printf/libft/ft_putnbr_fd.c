/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:05:31 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:59:00 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// write number into a file
// if the number is INT_MIN, write '-' & '2' first, then set n = 147483648
// why not just write '-' and set n = 2147483648?
// because INT_MAX is only 2147483647
// if the number is not INT_MIN and is less than zero, write '-', turn n to +
// if n greater than 9, meaning has 2 digit, call ft_putnbr_fd again by passing
// in n / 10 (get the number in the front)
// if n less than 10, meaning has 1 digit, convert the number to char and write
// into file
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(2 + '0', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		n = n % 10;
	}
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
}
