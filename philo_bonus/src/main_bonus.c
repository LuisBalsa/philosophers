/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:28:45 by luide-so          #+#    #+#             */
/*   Updated: 2023/10/24 14:50:15 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	create_and_check_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->pid[i] = fork();
		if (table->pid[i] == 0)
			philo_life(&table->philos[i]);
		else if (table->pid[i] < 0)
			return (error_msg("Error: Fork failed\n"), EXIT_FAILURE);
		i++;
	}
	if (table->n_meals
		&& pthread_create(&table->meals, NULL, check_meals, table) != 0)
		return (error_msg("Error: Thread failed\n"), EXIT_FAILURE);
	sem_wait(table->sem_stop);
	if (table->n_meals && pthread_detach(table->meals) != 0)
		return (error_msg("Error: Thread failed\n"), EXIT_FAILURE);
	return (0);
}

static void	init_semaphores(t_table *table)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_SATISFIED);
	sem_unlink(SEM_STOP);
	table->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644, table->n_philos);
	table->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	table->sem_satisfied = sem_open(SEM_SATISFIED, O_CREAT, 0644, 0);
	table->sem_stop = sem_open(SEM_STOP, O_CREAT, 0644, 0);
}

static void	init_table(t_table *table)
{
	int	i;

	table->pid = malloc(sizeof(pid_t) * table->n_philos);
	if (!table->pid)
		return (error_msg("Error: Failed to allocate memory\n"), exit(1));
	memset(table->pid, 0, sizeof(pid_t) * table->n_philos);
	table->philos = malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (free(table->pid),
			error_msg("Error: Failed to allocate memory\n"), exit(1));
	memset(table->philos, 0, sizeof(t_philo) * table->n_philos);
	init_semaphores(table);
	table->start_time = get_time();
	i = -1;
	while (++i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].table = table;
	}
}

static void	check_args(t_table *table, char **argv)
{
	if (atoi_mod(argv[1]) < 1 || atoi_mod(argv[2]) < 1
		|| atoi_mod(argv[3]) < 1 || atoi_mod(argv[4]) < 1
		|| (argv[5] && atoi_mod(argv[5]) < 0))
		return (error_msg("Error: Invalid arguments\n"), exit(1));
	if (argv[5] && atoi_mod(argv[5]) == 0)
		exit(0);
	table->n_philos = atoi_mod(argv[1]);
	table->time_to_die = atoi_mod(argv[2]);
	table->time_to_eat = atoi_mod(argv[3]);
	table->time_to_sleep = atoi_mod(argv[4]);
	if (argv[5])
		table->n_meals = atoi_mod(argv[5]);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		status;

	if (argc < 5 || argc > 6)
		return (error_msg("Error: Invalid number of arguments\n"), 1);
	memset(&table, 0, sizeof(t_table));
	check_args(&table, argv);
	init_table(&table);
	status = create_and_check_processes(&table);
	kill_philos(&table);
	free_table(&table);
	waitpid(-1, NULL, 0);
	return (status);
}
