/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:08:11 by luide-so          #+#    #+#             */
/*   Updated: 2023/10/24 14:52:07 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	free_table(t_table *table)
{
	if (table->pid)
		free(table->pid);
	if (table->philos)
		free(table->philos);
	sem_close(table->sem_forks);
	sem_close(table->sem_print);
	sem_close(table->sem_satisfied);
	sem_close(table->sem_stop);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_LAST_MEAL);
	sem_unlink(SEM_SATISFIED);
	sem_unlink(SEM_STOP);
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

void	error_msg(char *msg)
{
	if (!msg)
		return ;
	while (*msg)
		write(2, msg++, 1);
}

void	kill_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos && table->pid[i])
		kill(table->pid[i++], SIGKILL);
}
