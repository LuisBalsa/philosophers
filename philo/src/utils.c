/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:34:26 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/22 12:47:12 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].status_mutex);
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->dead);
	free(table->forks);
	free(table->philos);
}

suseconds_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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
