/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:14:12 by wricky-t          #+#    #+#             */
/*   Updated: 2022/06/08 16:48:21 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file descriptor is a number that uniquely identidies an open file in a
// computer's operating system
// the descriptor is identified by a unique non-negative integer, like 0,1,23.
// at least one file descriptor exists for every open file on the system
// on a unix-like os, the three file descriptors, by default, are:
// STDIN 0 (std input), STOUT 1 (std output) and STDERR 2 (std error)

// this function takes in one char and one file descriptor
// so what it does is write a character into the file by targeting it using
// file descriptor

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}
