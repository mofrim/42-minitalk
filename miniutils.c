/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:10:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/01 02:02:24 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_error(char *msg)
{
	ft_printf("%s\n", msg);
	exit(errno);
}

void	print_bitstr(unsigned char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0b10000000)
			ft_printf("1");
		else
			ft_printf("0");
		c <<= 1;
		i++;
	}
	ft_printf("\n");
}

void	signal_setup(void (*sig_handler)(int))
{
	struct sigaction	act;

	act.sa_handler = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		exit_error("sigaction error\n");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		exit_error("sigaction error\n");
}
