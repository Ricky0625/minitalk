/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/03 21:19:45 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void handle_server(int sig, siginfo_t *info, void *ucontext)
{
	// server status, 1 == active, 0 == offline
	// default is 0
	static int	status = 0;
	// store the binary value
	static int	binary = 0;
	// to keep track how many bit we receive
	static int	bit = 0;
	pid_t		client_pid;
	// commonly, handler function doesn't make any use of the third parameter
	// so typecast it to void
	(void)ucontext;
	// who send this signal?
	client_pid = info->si_pid;
	// check if server is ready to receive data
	if (sig == SIGUSR1 && status == 0)
	{
		// set server status to active
		status = 1;
		// ayoooo, i'm ready send me a bit please
		kill(client_pid, SIGUSR2);
	}
	else
	{
		// because the binary value server received is in reverse order
		// so this method can reverse back
		binary *= 10;
		// when the server is active, receive bit
		if (sig == SIGUSR1)
		{
			binary += 1;
			ft_printf("server is active, I received 1\n");
		}
		bit++;
		// here is if signal is SIGUSR2
		ft_printf("Server is active. I received 0\n");
		ft_printf("binary value: %d, bit: %d\n", binary, bit);
	}
}

// new server.c
int	main(void)
{
	struct sigaction	sa;
	// get server pid and print it out
	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_server;
	// hook sa to SIGUSR1 & SIGUSR2
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// wait for client's signal
	// 1. client send signal to check if server is ready
	while (1)
		pause();	
}