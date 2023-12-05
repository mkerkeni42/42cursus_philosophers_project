/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:55 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/05 15:04:49 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(char *message, t_philo *philo)
{
	pthread_mutex_lock(philo->rules->printer);
	printf("%ld %d %s\n", get_time() - philo->rules->start_time, \
		philo->id, message);
	pthread_mutex_unlock(philo->rules->printer);
}

int	check_death_signal(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->death_access);
	if (philo->rules->death_signal == 1)
	{
		pthread_mutex_unlock(philo->rules->death_access);
		return (1);
	}
	pthread_mutex_unlock(philo->rules->death_access);
	return (0);
}

static int	eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	if (check_death_signal(philo))
		return (1);
	pthread_mutex_lock(first_fork);
	log_message("has taken a fork", philo);
	if (philo->right_fork)
	{
		if (check_death_signal(philo))
		{
			pthread_mutex_unlock(first_fork);
			return (1);
		}
		pthread_mutex_lock(second_fork);
		log_message("has taken a fork", philo);
		log_message("is eating", philo);
		pthread_mutex_lock(philo->counter_access);
		philo->eat_counter++;
		pthread_mutex_unlock(philo->counter_access);
		pthread_mutex_lock(philo->meal_access);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->meal_access);
		ft_usleep(philo->rules->start_time, philo->rules->time_to_eat);
		pthread_mutex_unlock(second_fork);
	}
	pthread_mutex_unlock(first_fork);
	return (0);
}

static int	check_last_meal(t_philo *philo, int i)
{
	pthread_mutex_lock(philo[i].meal_access);
	if (get_time() - philo->last_meal >= philo->rules->time_to_die)
	{
		pthread_mutex_unlock(philo[i].meal_access);
		pthread_mutex_lock(philo[i].rules->death_access);
		philo[i].rules->death_signal = 1;
		pthread_mutex_unlock(philo[i].rules->death_access);
		log_message("died", philo);
		return (1);
	}
	pthread_mutex_unlock(philo[i].meal_access);
	return (0);
}

void	*death_handler(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = -1;
	while (++i < philo->rules->nb_of_philo)
	{
		pthread_mutex_lock(philo[i].counter_access);
		while (philo[i].eat_counter < philo->rules->min_eat_nb)
		{
			pthread_mutex_unlock(philo[i].counter_access);
			if (check_last_meal(philo, i))
				return (NULL);
			pthread_mutex_lock(philo[i].counter_access);
		}
		pthread_mutex_unlock(philo[i].counter_access);
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
		if (check_death_signal(philo))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (check_death_signal(philo))
			return (NULL);
		log_message("is sleeping", philo);
		ft_usleep(philo->rules->start_time, philo->rules->time_to_sleep);
		if (check_death_signal(philo))
			return (NULL);
		log_message("is thinking", philo);
	}
	return (NULL);
}
