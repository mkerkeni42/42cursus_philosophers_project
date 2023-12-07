/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:02:18 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/07 13:03:44 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_rules *rules)
{
	int	i;

	i = -1;
	rules->printer = malloc(sizeof(pthread_mutex_t));
	rules->death_access = malloc(sizeof(pthread_mutex_t));
	rules->end_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(rules->printer, NULL);
	pthread_mutex_init(rules->death_access, NULL);
	pthread_mutex_init(rules->end_lock, NULL);
	while (++i < rules->nb_of_philo)
		pthread_mutex_init(&rules->forks[i], NULL);
}

void	free_mutexes(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(rules->printer);
	pthread_mutex_destroy(rules->death_access);
	pthread_mutex_destroy(rules->end_lock);
	while (++i < rules->nb_of_philo)
	{
		pthread_mutex_destroy(philo[i].counter_access);
		pthread_mutex_destroy(philo[i].meal_access);
		pthread_mutex_destroy(&rules->forks[i]);
		free(philo[i].counter_access);
		free(philo[i].meal_access);
	}
	free(rules->forks);
	free(rules->printer);
	free(rules->death_access);
	free(rules->end_lock);
	free(philo);
	free(rules);
}
