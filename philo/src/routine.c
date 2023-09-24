/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:09:39 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/24 12:21:46 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	drop_forks(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->table->forks[id - 1]);
	philo->table->fork_taken[id - 1] = 0;
	pthread_mutex_unlock(&philo->table->forks[id - 1]);
	pthread_mutex_lock(&philo->table->forks[id % philo->table->n_philos]);
	philo->table->fork_taken[id % philo->table->n_philos] = 0;
	pthread_mutex_unlock(&philo->table->forks[id % philo->table->n_philos]);
}

static void	try_to_pick_up_forks(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->table->forks[id - 1]);
	while (philo->table->fork_taken[id - 1])
	{
		pthread_mutex_unlock(&philo->table->forks[id - 1]);
		satisfied_or_someone_died(philo);
		pthread_mutex_lock(&philo->table->forks[id - 1]);
	}
	philo->table->fork_taken[id - 1] = 1;
	pthread_mutex_unlock(&philo->table->forks[id - 1]);
	print_status(philo, FORKS);
	pthread_mutex_lock(&philo->table->forks[id % philo->table->n_philos]);
	while (philo->table->fork_taken[id % philo->table->n_philos])
	{
		pthread_mutex_unlock(&philo->table->forks[id % philo->table->n_philos]);
		satisfied_or_someone_died(philo);
		pthread_mutex_lock(&philo->table->forks[id % philo->table->n_philos]);
	}
	philo->table->fork_taken[id % philo->table->n_philos] = 1;
	pthread_mutex_unlock(&philo->table->forks[id % philo->table->n_philos]);
	print_status(philo, FORKS);
}

static int	sleeping(t_philo *philo)
{
	suseconds_t	current_time;

	current_time = get_time();
	if (print_status(philo, SLEEPING))
		try_to_pause_to_sleep(philo, current_time);
	return (!satisfied_or_someone_died(philo));
}

static int	eat(t_philo *philo, int id)
{
	suseconds_t	current_time;

	if (philo->table->n_philos == 1)
		return (print_status(philo, FORKS), 0);
	try_to_pick_up_forks(philo, id);
	current_time = get_time();
	pthread_mutex_lock(&philo->status_mutex);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->status_mutex);
	try_to_pause_to_eat(philo, current_time);
	drop_forks(philo, id);
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
		if (!eat(philo, philo->id))
			break ;
		if (!sleeping(philo))
			break ;
		if (!print_status(philo, THINKING))
			break ;
	}
	return (NULL);
}
