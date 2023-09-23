/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:06:58 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/23 18:36:09 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d%s", get_time() - philo->table->start_time,
		philo->id, DIED);
	pthread_mutex_unlock(&philo->table->print);
}

static int	monitor(t_table *table)
{
	int			i;
	static int	satisfied_count;

	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i].status_mutex);
		if (table->philos[i].status == SATISFIED)
		{
			satisfied_count++;
			table->philos[i].status = DONE;
		}
		if (table->philos[i].status != DONE
			&& get_time() - table->philos[i].last_meal > table->time_to_die)
		{
			pthread_mutex_lock(&table->dead);
			table->someone_died = 1;
			pthread_mutex_unlock(&table->dead);
			print_dead(&table->philos[i]);
			pthread_mutex_unlock(&table->philos[i].status_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].status_mutex);
	}
	return (satisfied_count != table->n_philos);
}

int	threads(t_table *t)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&t->dead);
	while (++i < t->n_philos)
	{
		if (pthread_create(&t->philos[i].thread, NULL, routine, &t->philos[i]))
			return (error_msg("Error: Failed to create thread\n"));
	}
	t->start_time = get_time();
	pthread_mutex_unlock(&t->dead);
	while (monitor(t))
		;
	i = -1;
	while (++i < t->n_philos)
	{
		if (pthread_join(t->philos[i].thread, NULL))
			return (error_msg("Error: Failed to join thread\n"));
	}
	return (0);
}
