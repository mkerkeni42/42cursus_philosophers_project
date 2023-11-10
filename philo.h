/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:16:17 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/10 14:47:00 by mkerkeni         ###   ########.fr       */
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

typedef struct s_rules {
	int	nb_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	min_eat_nb;
	int	eat_counter;
}		t_rules;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	*forks;
}					t_philo;

int			main(int ac, char **av);

long int	ft_atol(const char *str);

int			check_if_nb(char *arg);
int			parsing(int ac, char **av);

#endif
