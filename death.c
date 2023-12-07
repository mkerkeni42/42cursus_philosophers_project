/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:25:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/07 12:58:26 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	announce_death(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(rules->end_lock);
	if (rules->running_threads == 0)
		log_message("died", philo);
	pthread_mutex_unlock(rules->end_lock);
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

static int	check_last_meal(t_philo *philo, int i)
{
	pthread_mutex_lock(philo[i].meal_access);
	if (get_time() - philo->last_meal >= philo->rules->time_to_die)
	{
		pthread_mutex_unlock(philo[i].meal_access);
		pthread_mutex_lock(philo[i].rules->death_access);
		philo[i].rules->death_signal = 1;
		pthread_mutex_unlock(philo[i].rules->death_access);
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
