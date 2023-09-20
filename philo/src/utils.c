/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:34:26 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/20 02:45:19 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

suseconds_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000) + time.tv_usec);
}

int	atoi_mod(const char *nptr)
{
	int	nb;

	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
		nb = nb * 10 + (*nptr++ - '0');
	return (nb);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	return (1);
}
