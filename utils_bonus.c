/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:37:24 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/04 20:07:55 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minitalk.h"

int	sendchar(unsigned char c, int srv_pid, int *bits_sent);

void	printbyte(unsigned char c)
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
}

/* Send msg char by char to server. */
void	send_msg_print_bin(int srv_pid, char *msg)
{
	int	bits_sent;

	bits_sent = 0;
	ft_printf("Sending message to server at PID %d\n", srv_pid);
	while (*msg)
	{
		ft_printf("Sending byte: ");
		printbyte((unsigned char)*msg);
		sendchar((unsigned char)*msg, srv_pid, &bits_sent);
		ft_printf("\n");
		msg++;
	}
	ft_printf("Sending byte: ");
	printbyte((unsigned char)*msg);
	sendchar('\0', srv_pid, &bits_sent);
	ft_printf("\ndone!\n%d bits sent\n", bits_sent);
}
