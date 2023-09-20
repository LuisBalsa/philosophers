/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:06:58 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/20 02:07:30 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	start_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]))
			return (error_msg("Error: Failed to create thread\n"));
	}
	i = -1;
	while (++i < table->n_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (error_msg("Error: Failed to join thread\n"));
	}
	return (0);
}
