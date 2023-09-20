/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:09:39 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/20 04:18:56 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	satisfied_or_someone_died(t_philo *philo)
{
	if (philo->table->n_meals && philo->meal_count == philo->table->n_meals)
		return (1);
	pthread_mutex_lock(&philo->table->dead);
	if (philo->last_meal + philo->table->time_to_die < get_time())
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %d died\n", get_time() - philo->table->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->table->print);
		philo->table->someone_died = 1;
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	suseconds_t	time;
	suseconds_t	time2;

	time = get_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print);
	printf("%ld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	time2 = get_time() - philo->table->start_time;
	usleep(philo->table->time_to_sleep * 1000 - (time2 - time));
	return (!satisfied_or_someone_died(philo));
}

static int	eat(t_philo *philo, int id, int n_philos, suseconds_t s_time)
{
	int			first_fork;
	int			second_fork;
	int			eat;
	suseconds_t	time;

	first_fork = (id - (id % 2)) % n_philos;
	second_fork = (id - !(id % 2)) % n_philos;
	pthread_mutex_lock(&philo->table->forks[first_fork]);
	pthread_mutex_lock(&philo->table->forks[(id - !(id % 2)) % n_philos]);
	time = get_time() - philo->table->start_time;
	philo->last_meal = time;
	eat = !satisfied_or_someone_died(philo);
	if (eat)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %d has taken a fork\n", time, id);
		printf("%ld %d has taken a fork\n", time, id);
		printf("%ld %d is eating\n", time, id);
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->time_to_eat * 1000 - ((get_time() - s_time) - time));
	}
	pthread_mutex_unlock(&philo->table->forks[first_fork]);
	pthread_mutex_unlock(&philo->table->forks[second_fork]);
	philo->meal_count += (philo->table->n_meals > 0 && eat);
	return (eat);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (!eat(philo, philo->id, table->n_philos, table->start_time))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	return (NULL);
}
