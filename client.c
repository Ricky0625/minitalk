/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/03 21:20:01 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// use to store the message
// the reason of using global variable is that I can use it in handler function
// bcos there's no way to passing in string into handler function
char	*g_msg;

static void send_sig(pid_t server_pid, int char_dec)
{
	int			mask;
	// static int	bit = 0;

	mask = 128;
	(void)server_pid;
	// convert dec to binary and send it to server
	// this while loop is causing us cannot sent bit by bit
	while (mask > 0)
	{
		if (char_dec & mask)
		{
			ft_printf("sending 1\n");
			kill(server_pid, SIGUSR1);
		}
		else
		{
			ft_printf("sending 0\n");
			kill(server_pid, SIGUSR2);
		}
		mask >>= 1;
		// now is too fast
		// temporarily set this first
		usleep(50000);
	}
}

static void	handle_client(int sig, siginfo_t *info, void *ucontext)
{
	pid_t		server_pid;
	char		char_dec;
	static int	ith = 0;
	// commonly, the handler function doesn't make any use of the third argument
	// so typecast to void
	(void)ucontext;
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
		ft_printf("Received SIGUSR2\n");
		// testing: check if server could receive reply
		char_dec = *(g_msg + ith++); // pointer arithmetic
		// kill(server_pid, SIGUSR1);
		// we are passing a whole char here, might cause problem
		send_sig(server_pid, char_dec);
	}
}

// new client.c
int	main(int ac, char **av)
{
	pid_t				server_id;
	// new action to handle SIGUSR1 & SIGUSR2
	struct sigaction	sa;
	if (ac != 3)
	{
		ft_printf("Invalid usage!\n");
		exit(EXIT_FAILURE);
	}
	server_id = ft_atoi(av[1]);
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
	while (1)
		pause();
}