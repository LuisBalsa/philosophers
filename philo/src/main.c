/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:10:32 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/24 11:54:38 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->dead, NULL);
	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->philos[i].status_mutex, NULL);
	}
}

static int	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	table->n_philos = atoi_mod(argv[1]);
	table->time_to_die = atoi_mod(argv[2]);
	table->time_to_eat = atoi_mod(argv[3]);
	table->time_to_sleep = atoi_mod(argv[4]);
	if (argc == 6)
		table->n_meals = atoi_mod(argv[5]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	table->fork_taken = malloc(sizeof(int) * table->n_philos);
	ft_bzero(table->fork_taken, sizeof(int) * table->n_philos);
	table->philos = malloc(sizeof(t_philo) * table->n_philos);
	ft_bzero(table->philos, sizeof(t_philo) * table->n_philos);
	if (!table->philos || !table->forks)
		return (error_msg("Error: Failed to allocate memory\n"), 0);
	init_mutexes(table);
	table->start_time = get_time();
	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].table = table;
	}
	return (1);
}

static int	invalid_args(int argc, char **argv)
{
	if (atoi_mod(argv[1]) < 1 || atoi_mod(argv[2]) < 1
		|| atoi_mod(argv[3]) < 1 || atoi_mod(argv[4]) < 1
		|| (argc == 6 && atoi_mod(argv[5]) < 0))
		return (error_msg("Error: Invalid arguments\n"));
	if (argc == 6 && atoi_mod(argv[5]) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (error_msg("Error: Wrong number of arguments\n"));
	ft_bzero(&table, sizeof(t_table));
	if (invalid_args(argc, argv))
		return (1);
	if (!init_table(&table, argc, argv))
		return (1);
	if (threads(&table))
		return (1);
	free_table(&table);
	return (0);
}
