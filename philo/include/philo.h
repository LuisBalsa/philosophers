/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:42:53 by luide-so          #+#    #+#             */
/*   Updated: 2023/09/22 15:26:30 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED " died\n"

# define EAT 1
# define SLEEP 2

# define DONE 1
# define SATISFIED 2

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meal_count;
	int				status;
	pthread_mutex_t	status_mutex;
	suseconds_t		last_meal;
	struct s_table	*table;
}			t_philo;

typedef struct s_table
{
	int				n_philos;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	int				n_meals;
	suseconds_t		start_time;
	int				someone_died;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}				t_table;

int			threads(t_table *table);

void		*routine(void *arg);

void		try_to_pause_to_eat(t_philo *philo, suseconds_t start_time);
void		try_to_pause_to_sleep(t_philo *philo, suseconds_t start_time);
int			satisfied_or_someone_died(t_philo *philo);

void		free_table(t_table *table);
suseconds_t	get_time(void);
void		ft_putstr_fd(char *s, int fd);
int			atoi_mod(const char *nptr);
int			error_msg(char *msg);
int			print_status(t_philo *philo, char *status);

#endif
