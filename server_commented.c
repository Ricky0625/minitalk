/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/04 12:00:40 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	bin_to_dec(int binary)
{
	int	remainder;
	int	base;
	int	chardec;

	base = 1;
	chardec = 0;
	while (binary > 0)
	{
		remainder = binary % 10;
		if (remainder == 1)
			chardec += remainder * base;
		binary /= 10;
		base *= 2;
	}
	return (chardec);
}

static void handle_server(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	client_pid;
	// server status, 1 == active, 0 == offline
	// default is 0
	static int		status = 0;
	// store the binary value
	static int		binary = 0;
	// to keep track how many bit we receive
	static int		bit = 0;
	// commonly, handler function doesn't make any use of the third parameter
	// so typecast it to void
	(void)ucontext;
	// who send this signal?
	if (info->si_pid != 0 && client_pid != info->si_pid)
		client_pid = info->si_pid;
	// check if server is ready to receive data
	if (sig == SIGUSR1 && status == 0)
	{
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
			binary += 1;
		bit++;
		// check if receive 8 bit
		// convert the binary into decimal and print it out
		// then reset bit and binary to default
		if (bit == 8)
		{
			if (bin_to_dec(binary) == 0)
			{
				ft_printf("\n");
				status = 0;
				kill(client_pid, SIGUSR1);
			}
			ft_printf("%c", bin_to_dec(binary));
			bit = 0;
			binary = 0;
		}
		kill(client_pid, SIGUSR2);
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
	// 2. waiting to receive bit
	while (1)
		pause();	
}