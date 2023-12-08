/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:25:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/08 13:13:05 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_signal(t_philo *philo)
{
	pthread_mutex_lock(philo->rules->death_access);
	if (philo->rules->death_signal != 0)
	{
		pthread_mutex_unlock(philo->rules->death_access);
		return (1);
	}
	pthread_mutex_unlock(philo->rules->death_access);
	return (0);
}

static int	check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_access);
	if (get_time() - philo->last_meal >= philo->rules->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_access);
		pthread_mutex_lock(philo->rules->death_access);
		philo->rules->death_signal = 1;
		pthread_mutex_unlock(philo->rules->death_access);
		printf("%ld %d died\n", get_time() - philo->rules->start_time, \
			philo->id);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_access);
	return (0);
}

void	*death_handler(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = -1;
	while (1)
	{
		i = -1;
		while (++i < philo->rules->nb_of_philo)
		{
			if (check_last_meal(&philo[i]))
				return (NULL);
			pthread_mutex_lock(philo[i].counter_access);
			if (philo->rules->min_eat_nb != -1 
				&& philo[i].eat_counter == philo->rules->min_eat_nb)
			{
				pthread_mutex_unlock(philo[i].counter_access);
				return (NULL);
			}
			pthread_mutex_unlock(philo[i].counter_access);
		}
	}
	return (NULL);
}
