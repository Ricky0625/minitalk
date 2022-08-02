/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:54:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/02 21:26:47 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Print error message for invalid usage
**/
static void	invalid_argument(void)
{
	ft_printf("[ERROR]: INVALID USAGE!\n");
	ft_printf("[USAGE]: ./client pid msg\n");
}

/**
 * Convert decimal to binary
 * 
 * ith_bit	: ith bit
 * mask		: 
**/
static void	send_bit(pid_t server_pid, int char_dec)
{
	int	ith_bit;
	int	mask;

	ith_bit = -1;
	// pre-increment is faster
	while (++ith_bit < 8)
	{
		// need research
		mask = (1 << ith_bit);
		if (char_dec & mask)
			kill(server_pid, SIGUSR1); // SIGUSR1 represent 1
		else
			kill(server_pid, SIGUSR2); // SIGUSR2 represent 0
		// by default, the speed of signal being sent is too fast
		// so use usleep to slow it down
		usleep(500);
	}
}

/**
 * Convert char to dec and pass it to send_bit to convert it to binary
 * 
 * char_dec	: int value of char
 * 1. Iterate through the msg
 * 2. Typecase char to dec
 * 3. Pass the value to send_bit
**/
static void	parse_str(pid_t server_pid, char *msg)
{
	// store char's int value
	int	char_dec;

	// iterate through the string
	while (*msg != '\0')
	{
		char_dec = *msg;
		send_bit(server_pid, char_dec);
		msg++;
	}
}

/**
 * 1. check whether the ac is 3 or not (./client pid msg)
 * 2. parse the string (char -> dec -> bi)
**/
int	main(int ac, char **av)
{
	pid_t	server_pid;

	if (ac != 3)
	{
		invalid_argument();
		return (0);
	}
	server_pid = ft_atoi(av[1]);
	parse_str(server_pid, av[2]);
	ft_printf("Message sent!\n");
	return (0);
}
