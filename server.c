/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:05 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/04 18:19:06 by wricky-t         ###   ########.fr       */
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

static void	handle_server(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	client_pid;
	static int		status = 0;
	static int		binary = 0;
	static int		bit = 0;
	int				char_dec;

	(void)ucontext;
	char_dec = 0;
	if (info->si_pid != 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1 && status == 0)
		status = 1;
	else
	{
		binary *= 10;
		if (sig == SIGUSR1)
			binary += 1;
		bit++;
		if (bit == 8)
		{
			char_dec = bin_to_dec(binary);
			if (char_dec == 0)
			{
				write(1, "\n", 1);
				status = 0;
				kill(client_pid, SIGUSR1);
			}
			write(1, &char_dec, 1);
			bit = 0;
			binary = 0;
		}
	}
	kill(client_pid, SIGUSR2);
}

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
}
