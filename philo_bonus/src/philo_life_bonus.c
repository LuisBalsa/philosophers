/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:00:47 by luide-so          #+#    #+#             */
/*   Updated: 2023/10/24 13:59:12 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*check_meals(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *) arg;
	i = 0;
	if (table->n_meals == 0)
		return (NULL);
	while (i < table->n_philos)
	{
		sem_wait(table->sem_satisfied);
		i++;
	}
	sem_post(table->sem_stop);
	return (NULL);
}

static void	print_status(t_philo *philo, char *status)
{
	suseconds_t	time;

	time = get_time() - philo->table->start_time;
	sem_wait(philo->table->sem_print);
	printf("%ld %d %s\n", time, philo->id, status);
	sem_post(philo->table->sem_print);
}

static void	philo_routine(t_philo *philo)
{
	sem_wait(philo->table->sem_forks);
	print_status(philo, FORKS);
	sem_wait(philo->table->sem_forks);
	print_status(philo, FORKS);
	print_status(philo, EATING);
	sem_wait(philo->sem_last_meal);
	philo->last_meal = get_time();
	sem_post(philo->sem_last_meal);
	philo->meal_count++;
	if (philo->table->n_meals && philo->meal_count == philo->table->n_meals)
		sem_post(philo->table->sem_satisfied);
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
	print_status(philo, SLEEPING);
	usleep(philo->table->time_to_sleep * 1000);
	print_status(philo, THINKING);
	philo_routine(philo);
}

static void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		sem_wait(philo->sem_last_meal);
		if (get_time() - philo->last_meal > philo->table->time_to_die)
		{
			sem_wait(philo->table->sem_print);
			printf("%ld %d%s", get_time() - philo->table->start_time,
				philo->id, DIED);
			sem_post(philo->table->sem_stop);
			sem_post(philo->sem_last_meal);
			return (NULL);
		}
		sem_post(philo->sem_last_meal);
		usleep(5);
	}
	return (NULL);
}

void	philo_life(t_philo *philo)
{
	philo->sem_last_meal = sem_open(SEM_LAST_MEAL, O_CREAT, 0644, 1);
	pthread_create(&philo->thread, NULL, check_death, philo);
	usleep(philo->table->time_to_eat / 2 * 1000 * !(philo->id % 2));
	philo_routine(philo);
	pthread_join(philo->thread, NULL);
	sem_close(philo->sem_last_meal);
	exit(EXIT_SUCCESS);
}
