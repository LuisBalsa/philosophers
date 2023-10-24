/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:29:05 by luide-so          #+#    #+#             */
/*   Updated: 2023/10/24 14:35:28 by luide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

# define FORKS "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED " died\n"

# define SEM_FORKS "/forks"
# define SEM_PRINT "/print"
# define SEM_LAST_MEAL "/last_meal"
# define SEM_SATISFIED "/satisfied"
# define SEM_STOP "/stop"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meal_count;
	suseconds_t		last_meal;
	sem_t			*sem_last_meal;
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
	pid_t			*pid;
	t_philo			*philos;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_satisfied;
	sem_t			*sem_stop;
	pthread_t		meals;
}				t_table;

void		free_table(t_table *table);
suseconds_t	get_time(void);
int			atoi_mod(const char *nptr);
void		error_msg(char *msg);
void		ft_bzero(void *s, size_t n);

void		*check_meals(void *arg);
void		philo_life(t_philo *philo);
void		kill_philos(t_table *table);

#endif
