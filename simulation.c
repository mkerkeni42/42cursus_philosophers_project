/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/14 15:30:36 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_message(char *message, int id, struct timeval *start_time)
{
	long			elapsed_time;

	elapsed_time = get_time(start_time);
	printf("%ld %d %s\n", elapsed_time, id, message);
}

void	*philo_life(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		log_message("is thinking", philo->id, philo->start_time);
		usleep(100000);
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		log_message("has taken a fork", philo->id, philo->start_time);
		log_message("is eating", philo->id, philo->start_time);
		usleep(100000);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		log_message("is sleeping", philo->id, philo->start_time);
		usleep(100000);
	}
	return (NULL);
}
