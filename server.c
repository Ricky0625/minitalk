/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/06 15:03:48 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Print out the character
 * 
 * 1. Check if the char_out is '\0', if yes, meaning we reached the end of
 *    the string. Print a newline. Also, set server to offline, so that
 *    it can wait for another client to send data
 * 2. If not '\0', print out the character
**/
static void	print_out(char char_out, pid_t client_pid, int *status)
{
	if (char_out == '\0')
	{
		char_out = '\n';
		*status = 0;
		kill(client_pid, SIGUSR1);
	}
	write(1, &char_out, 1);
}

/**
 * Action to perform when server receive the signal
 * 
 * 1. Need to check if the si_pid is 0 or not because sometimes si_pid
 *    is zero. If that's the case, don't update client_pid, use the
 * 	  previous one instead.
 * 2. The first signal that the server will receive from client is to check
 * 	  if server is ready to receive data. If yes, set status to 1, meaning
 *    server is now online, ready to receive data.
 * 3. When server is online and receive signal. These signals are the data.
 * 	  Here I'm using bitwise operator to reverse the bits, bcos what server
 * 	  receive is in reverse order
 * 4. If server received 8 bit, convert it into character and print it out
**/
static void	handle_server(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	client_pid = 0;
	static int		status = 0;
	static char		char_out = 0;
	static int		bit = 0;

	(void)ucontext;
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1 && status == 0)
		status = 1;
	else
	{
		char_out <<= 1;
		if (sig == SIGUSR1)
			char_out += 1;
		bit++;
		if (bit == 8)
		{
			print_out(char_out, client_pid, &status);
			bit = 0;
		}
	}
	kill(client_pid, SIGUSR2);
}

/**
 * The server (Two way communication)
 * 
 * 1. print the server pid
 * 2. hook the new-defined action to the signls (SIGUSR1 & SIGUSR2)
 * 3. while pause is to wait fro signal from client
**/
int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
