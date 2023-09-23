/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:09:39 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/23 23:39:36 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	sleeping(t_philo *philo)
{
	suseconds_t	current_time;

	current_time = get_time();
	if (print_status(philo, SLEEPING))
		try_to_pause_to_sleep(philo, current_time);
	return (!satisfied_or_someone_died(philo));
}

static int	eat(t_philo *philo, int id, int n_philos)
{
	suseconds_t	current_time;

	pthread_mutex_lock(&philo->table->forks[id % n_philos]);
	print_status(philo, FORKS);
	if (philo->table->n_philos == 1)
		return (0);
	pthread_mutex_lock(&philo->table->forks[id - 1]);
	current_time = get_time();
	pthread_mutex_lock(&philo->status_mutex);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->status_mutex);
	if (print_status(philo, FORKS))
		try_to_pause_to_eat(philo, current_time);
	pthread_mutex_unlock(&philo->table->forks[id % n_philos]);
	pthread_mutex_unlock(&philo->table->forks[id - 1]);
	return (!satisfied_or_someone_died(philo));
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_table		*table;
	suseconds_t	time_pause_even;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&table->dead);
	pthread_mutex_unlock(&table->dead);
	time_pause_even = philo->table->time_to_eat * !(philo->id % 2) * 1000;
	usleep(time_pause_even
		* (philo->table->time_to_eat < philo->table->time_to_die));
	while (1)
	{
		if (!eat(philo, philo->id, table->n_philos))
			break ;
		if (!sleeping(philo))
			break ;
		if (!print_status(philo, THINKING))
			break ;
	}
	return (NULL);
}
