/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaurer <fmaurer42@posteo.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:48:43 by fmaurer           #+#    #+#             */
/*   Updated: 2024/09/04 20:12:07 by fmaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <unistd.h>
# include <signal.h>
# include <errno.h>

/* Timeout with error after 20*10ms = 200ms. */
# define ACK_TIMEOUT 20

void	exit_error(char *msg);
void	signal_setup(void (*sig_handler)(int));
void	sig_handler(int signum);
void	send_msg(int srv_pid, char *msg);
int		sendchar(unsigned char c, int srv_pid, int *bits_sent);
void	send_sig(int srv_pid, int signum);

#endif
