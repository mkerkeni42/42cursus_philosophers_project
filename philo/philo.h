/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:16:17 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/08 13:18:51 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				nb_of_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				min_eat_nb;
	int				death_signal;
	long int		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printer;
	pthread_mutex_t	death_access;
}					t_rules;

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	long int		last_meal;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	counter_access;
	pthread_mutex_t	meal_access;
}					t_philo;

typedef struct s_fork
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}					t_fork;

int			main(int ac, char **av);

long int	ft_atol(const char *str);

int			parsing(int ac, char **av);

void		free_mutexes(t_rules *rules, t_philo *philo);
void		init_mutexes(t_rules *rules);

void		*philo_life(void *arg);
void		log_message(char *message, t_philo *philo);

void		*death_handler(void *arg);
int			check_death_signal(t_philo *philo);

long		get_time(void);
void		ft_usleep(long int start, long int time, t_philo *philo);
void		sleep_odd_philo(t_philo *philo, int x);

#endif
