/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:34:26 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/24 12:41:23 by luide-so         ###   ########.fr       */
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
	free(table->fork_taken);
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

int	error_msg(char *msg)
{
	if (!msg)
		return (0);
	while (*msg)
		write(2, msg++, 1);
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	while (n-- > 0)
		*p++ = '\0';
}
