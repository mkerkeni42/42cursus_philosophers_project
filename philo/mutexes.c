/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:02:18 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/11 12:47:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	i = -1;
	pthread_mutex_init(&rules->printer, NULL);
	pthread_mutex_init(&rules->death_access, NULL);
	while (++i < rules->nb_of_philo)
		pthread_mutex_init(&rules->forks[i], NULL);
}

void	free_mutexes(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&rules->printer);
	pthread_mutex_destroy(&rules->death_access);
	while (++i < rules->nb_of_philo)
	{
		pthread_mutex_destroy(&philo[i].counter_access);
		pthread_mutex_destroy(&philo[i].meal_access);
		pthread_mutex_destroy(&rules->forks[i]);
	}
	free(rules->forks);
	free(philo);
	free(rules);
}
