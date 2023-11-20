/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/20 15:35:42 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->printer);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->rules->printer);
}

void	*philo_life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (philo->rules->min_eat_nb > 0)
	{
		if (philo->id % 2 == 0)
			usleep(1000);
		pthread_mutex_lock(&philo->left_fork);
		log_message("has taken the left fork", philo);
		pthread_mutex_lock(&philo->right_fork);
		log_message("has taken the right fork", philo);
		log_message("is eating", philo);
		ft_usleep(philo->start_time, philo->rules->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		log_message("is sleeping", philo);
		ft_usleep(philo->start_time, philo->rules->time_to_sleep);
		if (get_time() - philo->start_time >= philo->rules->time_to_die)
		{
			log_message("died", philo);
			break ;
		}
		log_message("is thinking", philo);
		philo->rules->min_eat_nb--;
	}
	return (NULL);
}
