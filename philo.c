/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/09 15:25:31 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_data *philo, int ac, char **av)
{
	philo->nb_of_philo = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		philo->eat_nb = ft_atol(av[5]);
	else
		philo->eat_nb = 0;
}

int	main(int ac, char **av)
{
	t_data	*philo;

	if (parsing(ac, av))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_data));
	if (!philo)
		return (EXIT_FAILURE);
	init_philo(philo, ac, av);
	return (EXIT_SUCCESS);
}
