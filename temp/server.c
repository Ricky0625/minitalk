/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:53:50 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/03 16:43:37 by wricky-t         ###   ########.fr       */
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

static void	print_msg(pid_t client_id, int binary)
{
	int	char_dec;
	
	char_dec = bin_to_dec(binary);
	if (char_dec == 0)
	{
		ft_printf("\n");
		kill(client_id, SIGUSR1);
		exit(EXIT_SUCCESS);
	}
	ft_printf("%c", char_dec);
	kill(client_id, SIGUSR2);
}

static void handle_server(int sig, siginfo_t *info, void *ucontext)
{
	pid_t			client_pid;
	static int		binary = 0;
	static int		bit = 0;
	static int		connected = 0;

	(void)ucontext;
	client_pid = info->si_pid;
	// check if server could receive signal from client
	if (sig == SIGUSR1 && connected == 0)
	{
		// set connected to 1, meaning the server can receive signal from client
		connected = 1;
		kill(client_pid, SIGUSR2);
	}
	if ((sig == SIGUSR1 || sig == SIGUSR2) && connected == 1)
	{
		ft_printf("sig: %d\n", sig);
		// receive signal as save it as binary
		if (sig == SIGUSR1)
		{
			binary *= 10;
			binary += 1;
		}
		else if (sig == SIGUSR2)
			binary *= 10;
		printf("%d\n", bit);
		// if received 8 bit
		if (bit == 8)
		{
			// print the character
			print_msg(client_pid, binary);
			bit = 0;
			binary = 0;
		}
	}
}

/**
 * server
 * 
 * sa : sigaction struct
 * pid: server pid
 * 
 * 1. get PID and print it out
 * 2. hook user defined action to SIGUSR1 & SIGUSR2
 * 3. the while loop is to wait for any signal
**/
int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
