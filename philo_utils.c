/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:11:02 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/05 09:38:11 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atol(const char *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	result = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	free_mutexes(t_rules *rules, t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(rules->printer);
	pthread_mutex_destroy(rules->death_access);
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
	free(philo);
	free(rules);
}
