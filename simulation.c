/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/23 15:46:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->printer);
	printf("%ld %d %s\n", get_time() - philo->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->rules->printer);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_message("has taken the left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	log_message("has taken the right fork", philo);
	log_message("is eating", philo);
	philo->eat_counter++;
	philo->last_meal = get_time();
	ft_usleep(philo->start_time, philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*death_handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (philo->eat_counter < philo->rules->min_eat_nb)
	{
		if (get_time() - philo->last_meal >= philo->rules->time_to_die)
		{
			log_message("died", philo);
			return (NULL);
		}
	}
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->eat_counter < philo->rules->min_eat_nb)
	{
		if (philo->id % 2 == 0)
		{
			if (philo->eat_counter == 0)
				log_message("is thinking", philo);
			usleep(1000);
		}
		eating(philo);
		log_message("is sleeping", philo);
		ft_usleep(philo->start_time, philo->rules->time_to_sleep);
		log_message("is thinking", philo);
	}
	return (NULL);
}
