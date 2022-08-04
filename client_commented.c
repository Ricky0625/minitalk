/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/04 12:17:26 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// use to store the message
// the reason of using global variable is that I can use it in handler function
// bcos there's no way to passing in string into handler function
char	*g_msg;

static void send_sig(pid_t server_pid, int char_dec)
{
	// set as static so that next time we call, can resume back to what's left
	static int	mask = 128;
	static int	bit = 0;

	// convert dec to binary and send it to server
	// this while loop is causing us cannot sent bit by bit
	// while (mask > 0)
	// {
	// if bit == 8, meaning last time received signal, we already transmitted 8 bit
	// suppose the char_dec will be a new one, so reset bit and mask to default
	if (bit == 8)
	{
		mask = 128;
		bit = 0;
	}
	// BITWISE AND
	if (char_dec & mask)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	mask >>= 1;
	// keep track how many bit has sent
	bit++;
	usleep(10);
}

static void	handle_client(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	server_pid;
	char			char_dec;
	// process ith's character
	static int		ith = 0;
	// use to check how many bit we sent
	static int		bit = 0;
	// commonly, the handler function doesn't make any use of the third argument
	// so typecast to void
	(void)ucontext;
	// bcos sometimes info->si_pid is 0, so cannot directly set
	// need to check first, so if si_pid is 0, use the previous one
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (sig == SIGUSR1)
	{
		ft_printf("Message received! \n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		// don't think any signal beside SIGUSR2 will invoke this block
		// if server is ready, this block will be invoked
		// ft_printf("Received SIGUSR2\n");
		// to check if client ady sent 8 bit or not
		// if yes then get to next character
		if (bit == 8)
		{
			bit = 0;
			ith++;
		}
		char_dec = *(g_msg + ith); // pointer arithmetic
		// passing a whole char here doesn't matter
		// because char_dec will always be constant, just for comparison purpose
		send_sig(server_pid, char_dec);
		// keep track how many bit client has sent
		bit++;
	}
}

// new client.c
int	main(int ac, char **av)
{
	pid_t				server_id;
	// new action to handle SIGUSR1 & SIGUSR2
	struct sigaction	sa;

	// check argument count
	if (ac != 3)
	{
		ft_printf("Invalid usage!\n");
		exit(EXIT_FAILURE);
	}
	// set server_id
	server_id = ft_atoi(av[1]);
	// set message
	g_msg = av[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_client;
	// hook handle_client to SIGUSR1 & SIGUSR2
	// so that when client receive those signal, they know how to react
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// check if server is ready to receive data
	// ayooo, are you ready??????
	kill(server_id, SIGUSR1);
	// wait for server's signal
	// 1. server ready to receive data
	// 2. server send message received signal
	while (1)
		pause();
}