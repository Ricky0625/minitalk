/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:53:50 by wricky-t          #+#    #+#             */
/*   Updated: 2022/08/02 21:20:44 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * Action to be performed when received sigusr1 signal
**/
void	handle_sigusr1(int sig)
{
	sig = 1;
	ft_printf("1");
}

/**
 * Action to be performed when received sigusr2 signal
**/
void	handle_sigusr2(int sig)
{
	sig = 0;
	ft_printf("0");
}

/**
 * Hook the user-defined action to the signal
 * sig	: signal
 * sa	: struct for sigaction
 * act	: function pointer that points to the handler function
 * 
 * 1. sigemptyset to empty the sa_mask so no signal will be blocked
 * 2. set sa_handler to act, so that when received sig, perform what has been
 * 	  defined in act
 * 3. set SA_RESTART to sa_flags so that when signal blocked by slow system
 *    call, let signal do what it suppose to do first then invoke the
 *    syscall again.
**/
static void	hook_signal(int sig, struct sigaction *sa, void (*act)(int sig))
{
	sigemptyset(&sa->sa_mask);
	sa->sa_handler = act;
	sa->sa_flags = SA_RESTART;
	sigaction(sig, sa, NULL);
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
	struct sigaction	sa_usr1;
	struct sigaction	sa_usr2;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	hook_signal(SIGUSR1, &sa_usr1, &handle_sigusr1);
	hook_signal(SIGUSR2, &sa_usr2, &handle_sigusr2);
	while (1)
		pause();
	return (0);
}
