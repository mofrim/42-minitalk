/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:49:25 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/04 14:22:48 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* The server signal_handler. If we receive SIGUSR2 from client set bits from
 * left to right by bitwise or. (unsigned char)128 = 0b10000000 but i prefer
 * explicitness over shortness here. */
void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int		i;
	static unsigned char	c;

	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		c |= (0b10000000 >> i);
	i++;
	if (i == 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		i = 0;
	}
}

/* Main. Using SA_SIGINFO here because we need the pid of the client which will
 * be saved in siginfo_t struct. SIGUSR* is added to sa_mask in order to block
 * both signals during handler execution. */
int	main(void)
{
	pid_t				pid;
	struct sigaction	sig_act;

	pid = getpid();
	ft_printf("%d\n", pid);
	sig_act.sa_sigaction = &signal_handler;
	sig_act.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_act.sa_mask);
	sigaddset(&sig_act.sa_mask, SIGUSR1);
	sigaddset(&sig_act.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);
	while (1)
		pause();
	return (0);
}
