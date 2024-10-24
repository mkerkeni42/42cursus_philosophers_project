/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:28:48 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/20 15:35:54 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int start, long int time, t_philo *philo)
{
	long int	elapsed_time;

	elapsed_time = get_time() - start;
	while (get_time() - start < elapsed_time + time)
	{
		if (check_death_signal(philo))
			break ;
		usleep(200);
	}
}

void	sleep_odd_philo(t_philo *philo)
{
	if (philo->rules->nb_of_philo % 2)
		ft_usleep(philo->rules->start, (philo->rules->time_to_eat \
		- philo->rules->time_to_sleep) * 2, philo);
}
