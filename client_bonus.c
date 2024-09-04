/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:40:08 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/04 17:10:11 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minitalk.h"

void	send_msg(int srv_pid, char *msg);
int		sendchar(unsigned char c, int srv_pid, int *bits_sent);
void	send_sig(int srv_pid, int signum);

/* Main. If i'd allow srv_pid < 0, it could set to -1. kill(-1, SIGUSR1)
 * terminates all my processes. Check that on campus.  */
int	main(int ac, char **av)
{
	pid_t	srv_pid;

	if (ac != 3 && ac != 4)
	{
		ft_printf("Usage: %s SERVER_PID MESSAGE\n", av[0]);
		return (0);
	}
	if (ac == 3)
	{
		srv_pid = ft_atoi(av[1]);
		if ((kill(srv_pid, 0) == -1) || srv_pid < 0)
			exit_error("Wrong PID or no permission to kill PID.\n");
		send_msg(srv_pid, av[2]);
		return (0);
	}
	if (ac == 4)
	{
		if (ft_strncmp(av[1], "-u", 2))
		{
			ft_printf("Bonus usage: %s -u SERVER_PID MESSAGE\n", av[0]);
			return (0);
		}
	}
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
		usleep(50);
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
	}
	return (0);
}

/* Sends the specified Signal to srv_pid. Wait until server sends SIGUSR1 as
 * back as Ack. For each 10ms timeout print a space char. */
void	send_sig(int srv_pid, int signum)
{
	kill(srv_pid, signum);
	usleep(100);
}

/* Some unicode symbols:
 *
 * ۺ 😆😆😆😆 ϕ ζ η θ ι κ λ μ ν ξ ο π ρ ς σ τ υ φ χ ψ ω ϊ ϋ ό ύ ώ Ϗ ϐ ϑ ϒ ϓ ϔ ϕ
 * ϖ ϗ Ϙ ϙ Ϛ ϛ Ϝ ϝ Ϟ ϟ Ϡ ϡ Ϣ ϣ Ϥ ϥ Ϧ ϧ Ϩ ϩ Ϫ ϫ Ϭ ϭ Ϯ ϯ ϰ ϱ ϲ ϳ ϴ ϵ ϶ Ϸ ϸ Ϲ Ϻ ϻ ϼ
 * Ͻ Ͼ Ͽ
 *
 * 1 byte = 8 bit:	a
 * 2 bytes = 16bit:	ۺ
 * 3 bytes = 24bit:	﷽﷽
 * 4 bytes = 32bit:	😆
 */
