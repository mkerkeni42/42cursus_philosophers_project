/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/08 13:10:23 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->death_access);
	if (philo->rules->death_signal == 0)
	{
		pthread_mutex_unlock(&philo->rules->death_access);
		pthread_mutex_lock(&philo->rules->printer);
		printf("%ld %d %s\n", get_time() - philo->rules->start, \
			philo->id, message);
		pthread_mutex_unlock(&philo->rules->printer);
		return ;
	}
	pthread_mutex_unlock(&philo->rules->death_access);
}

static t_fork	*get_forks(t_philo *philo, t_fork *forks)
{
	if (philo->id % 2 == 0)
	{
		forks->first_fork = philo->right_fork;
		forks->second_fork = philo->left_fork;
	}
	else
	{
		forks->first_fork = philo->left_fork;
		forks->second_fork = philo->right_fork;
	}
	return (forks);
}

static void	take_second_fork(t_philo *philo, t_fork *forks)
{
	pthread_mutex_lock(forks->second_fork);
	log_message("has taken a fork", philo);
	log_message("is eating", philo);
	pthread_mutex_lock(&philo->counter_access);
	philo->eat_counter++;
	pthread_mutex_unlock(&philo->counter_access);
	pthread_mutex_lock(&philo->meal_access);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_access);
	ft_usleep(philo->rules->start, philo->rules->time_to_eat, philo);
	pthread_mutex_unlock(forks->first_fork);
	pthread_mutex_unlock(forks->second_fork);
}

static int	eating(t_philo *philo)
{
	t_fork	*forks;

	forks = malloc(sizeof(t_fork));
	forks = get_forks(philo, forks);
	pthread_mutex_lock(forks->first_fork);
	log_message("has taken a fork", philo);
	if (philo->right_fork)
		take_second_fork(philo, forks);
	else
	{
		pthread_mutex_unlock(forks->first_fork);
		free(forks);
		return (1);
	}
	free(forks);
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_death_signal(philo))
			break ;
		if (philo->rules->min_eat_nb != -1
			&& philo->eat_counter == philo->rules->min_eat_nb)
			break ;
		if (philo->id % 2 == 0)
		{
			if (philo->eat_counter == 0)
				log_message("is thinking", philo);
			usleep(1000);
		}
		if (eating(philo))
			break ;
		log_message("is sleeping", philo);
		ft_usleep(philo->rules->start, philo->rules->time_to_sleep, philo);
		sleep_odd_philo(philo);
		log_message("is thinking", philo);
	}
	return (NULL);
}
