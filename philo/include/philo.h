/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:42:53 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/20 03:48:18 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meal_count;
	suseconds_t		last_meal;
	pthread_mutex_t	last_meal_mutex;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				someone_died;
	suseconds_t		start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_table;

void		*routine(void *arg);

suseconds_t	get_time(void);
void		ft_putstr_fd(char *s, int fd);
int			atoi_mod(const char *nptr);
int			error_msg(char *msg);

#endif
