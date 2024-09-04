/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:40:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/04 10:02:56 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_srv_ack;

void	sig_handler(int signum);
void	send_msg(int srv_pid, char *msg);
int		sendchar(unsigned char c, int srv_pid, int *bits_sent);
void	send_sig(int srv_pid, int signum);

/* Main. If i'd allow srv_pid < 0, it could set to -1. kill(-1, SIGUSR1)
 * terminates all my processes. Check that on campus.  */
int	main(int ac, char **av)
{
	pid_t	srv_pid;

	if (ac != 3)
	{
		ft_printf("Usage: %s SERVER_PID MESSAGE\n", av[0]);
		return (0);
	}
	srv_pid = ft_atoi(av[1]);
	if ((kill(srv_pid, 0) == -1) || srv_pid < 0)
		exit_error("Wrong PID or no permission to kill PID.\n");
	signal_setup(&sig_handler);
	send_msg(srv_pid, av[2]);
	return (0);
}

/* The client signal Handler. For SIGUSR2, which means server has reveived one
 * complete byte, print a dot. For SIGUSR1, which means server has received a
 * single bit, set global acknowledgement var to 1. */
void	sig_handler(int signum)
{
	if (signum == SIGUSR2)
		ft_putchar_fd('.', 1);
	if (signum == SIGUSR1)
		g_srv_ack = 1;
}

/* Send msg char by char to server. */
void	send_msg(int srv_pid, char *msg)
{
	int	bits_sent;

	bits_sent = 0;
	ft_printf("Sending message to server at PID %d\n", srv_pid);
	while (*msg)
	{
		sendchar((unsigned char)*msg, srv_pid, &bits_sent);
		msg++;
	}
	sendchar('\0', srv_pid, &bits_sent);
	ft_printf(" done!\n%d bits sent\n", bits_sent);
}

/* Send char to server. SIGUSR1 = 0, SIGUSR2 = 1. Reading each char from left to
 * right. */
int	sendchar(unsigned char c, int srv_pid, int *bits_sent)
{
	int	bit_indx;

	bit_indx = 0;
	while (bit_indx < 8)
	{
		if ((c << bit_indx) & 0b10000000)
			send_sig(srv_pid, SIGUSR2);
		else
			send_sig(srv_pid, SIGUSR1);
		(*bits_sent)++;
		bit_indx++;
		g_srv_ack = 0;
	}
	return (0);
}

/* Sends the specified Signal to srv_pid. Wait until server sends SIGUSR1 as
 * back as Ack. For each 10ms timeout print a space char. */
void	send_sig(int srv_pid, int signum)
{
	int	timeout;

	timeout = 0;
	kill(srv_pid, signum);
	usleep(10);
	while (!g_srv_ack && timeout < ACK_TIMEOUT)
	{
		ft_putchar_fd(' ', 1);
		usleep(10);
		timeout++;
	}
	if (timeout == ACK_TIMEOUT && !g_srv_ack)
	{
		errno = ETIMEDOUT;
		exit_error("Server Timeout\n");
	}
}
