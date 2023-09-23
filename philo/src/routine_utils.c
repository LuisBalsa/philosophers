/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:27:43 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/23 20:40:42 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	satisfied_or_someone_died(t_philo *philo)
{
	if (philo->table->n_meals && philo->meal_count == philo->table->n_meals)
	{
		pthread_mutex_lock(&philo->status_mutex);
		philo->status = SATISFIED;
		pthread_mutex_unlock(&philo->status_mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->table->dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead);
	return (0);
}

void	try_to_pause_to_eat(t_philo *philo, suseconds_t start_time)
{
	suseconds_t	time_start_eating;

	if (!satisfied_or_someone_died(philo) && print_status(philo, EATING))
	{
		time_start_eating = get_time() - start_time;
		usleep((philo->table->time_to_eat - time_start_eating) * 1000);
		if (philo->table->n_meals > 0)
			philo->meal_count++;
	}
}

void	try_to_pause_to_sleep(t_philo *philo, suseconds_t start_time)
{
	suseconds_t	time_start_sleeping;

	time_start_sleeping = get_time() - start_time;
	usleep((philo->table->time_to_sleep - time_start_sleeping) * 1000);
}

int	print_status(t_philo *philo, char *status)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->table->dead);
	if (philo->table->someone_died)
		return (pthread_mutex_unlock(&philo->table->dead), 0);
	pthread_mutex_unlock(&philo->table->dead);
	pthread_mutex_lock(&philo->table->print);
	time = get_time() - philo->table->start_time;
	printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->table->print);
	return (1);
}
