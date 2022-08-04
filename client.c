/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 20:12:07 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/04 17:56:15 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_msg;

static void	send_sig(pid_t server_pid, int char_dec)
{
	static int	mask = 128;
	static int	bit = 0;

	if (bit == 8)
	{
		mask = 128;
		bit = 0;
	}
	if (char_dec & mask)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	mask >>= 1;
	bit++;
	usleep(15);
}

static void	handle_client(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t	server_pid;
	char			char_dec;
	static int		ith = 0;
	static int		bit = 0;

	(void)ucontext;
	if (info->si_pid != 0)
		server_pid = info->si_pid;
	if (sig == SIGUSR1)
	{
		ft_printf("Message received!\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (bit == 8)
		{
			bit = 0;
			ith++;
		}
		char_dec = *(g_msg + ith);
		send_sig(server_pid, char_dec);
		bit++;
	}
}

int	main(int ac, char **av)
{
	pid_t				server_id;
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_printf("[ERROR]: Invalid usage!\n");
		ft_printf("[USAGE]: ./client [pid] [msg]\n");
		exit(EXIT_FAILURE);
	}
	server_id = ft_atoi(av[1]);
	g_msg = av[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_client;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	kill(server_id, SIGUSR1);
	while (1)
		pause();
}
