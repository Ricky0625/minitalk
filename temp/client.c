/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:54:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/03 16:36:53 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_msg;

/**
 * Print error message for invalid usage
**/
static void	invalid_argument(void)
{
	ft_printf("[ERROR]: INVALID USAGE!\n");
	ft_printf("[USAGE]: ./client pid msg\n");
}

/**
 * Convert decimal to binary and send to server
 * 
 * ith_bit	: ith bit
 * mask		:
 * The bit will be sent in reverse order, so server should reverse the bit
 * For example: 00010110 (h in reverse)
**/
static void	send_sig(pid_t server_pid, int char_dec)
{
	int mask;
	// int	mask;

	mask = 128;
	while (mask > 0)
	{
		// need research
		if (char_dec & mask)
		{
			ft_printf("1");
			kill(server_pid, SIGUSR1); // SIGUSR1 represent 1
		}
		else
		{
			ft_printf("0");
			kill(server_pid, SIGUSR2); // SIGUSR2 represent 0
		}
		mask >>= 1;
	}
}

/**
 * Convert char to dec and pass it to send_sig to convert it to binary
 * 
 * char_dec	: int value of char
 * 1. Iterate through the msg
 * 2. Typecase char to dec
 * 3. Pass the value to send_sig
**/
// static void	parse_str(pid_t server_pid, char ch)
// {
// 	// store char's int value
// 	int	char_dec;

// 	char_dec = ch;
// 	send_sig(server_pid, char_dec);
// 	send_sig(server_pid, 0);
// }

static void handle_client(int sig, siginfo_t *info, void *ucontext)
{
	pid_t		server_pid;
	static int	ith_char = 0;
	char		ch;

	(void)ucontext;
	server_pid = info->si_pid;
	// received all message
	if (sig == SIGUSR1)
	{
		ft_printf("Message Received!\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_printf("server confirmed they can receive signal\n");
		// process of server asking client to send another bit
		// if client receive SIGUSR2 signal meaning, server successfully receive one bit
		// requesting for another bit
		ch = g_msg[ith_char++]; // pointer arithmetic
		if (ch == 0)
			send_sig(server_pid, 0);
		send_sig(server_pid, ch);
	}
}

/**
 * 1. check whether the ac is 3 or not (./client pid msg)
 * 2. parse the string (char -> dec -> bi)
**/
int	main(int ac, char **av)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (ac != 3)
	{
		invalid_argument();
		return (0);
	}
	server_pid = ft_atoi(av[1]);
	g_msg = av[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_client;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// check if server is ready to receive data
	kill(server_pid, SIGUSR1);
	// waiting for signal from server
	while (1)
		pause();
	return (0);
}
