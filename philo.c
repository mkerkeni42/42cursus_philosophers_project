/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/14 15:30:21 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_rules *rules, t_philo *philo, int i)
{
	if (i == 0)
		philo[i].left_fork = rules->forks[rules->nb_of_philo - 1];
	else
		philo[i].left_fork = rules->forks[i - 1];
	if (i == rules->nb_of_philo - 1)
		philo[i].right_fork = rules->forks[0];
	else
		philo[i].right_fork = rules->forks[i];
}

static int	create_philos(t_rules *rules)
{
	t_philo			*philo;
	int				i;
	struct timeval	start_time;

	i = -1;
	gettimeofday(&start_time, NULL);
	philo = malloc(sizeof(t_philo));
	while (++i < rules->nb_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].rules = rules;
		philo[i].start_time = &start_time;
		get_forks(rules, philo, i);
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
			write(2, "Failed to create thread\n", 25);
	}
	i = -1;
	while (++i < rules->nb_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			write(2, "Failed to wait for the thread to finish\n", 41);
	}
	return (0);
}

static int	init_rules(t_rules *rules, int ac, char **av)
{
	int	i;

	i = -1;
	rules->nb_of_philo = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	rules->eat_counter = 0;
	if (ac == 6)
		rules->min_eat_nb = ft_atol(av[5]);
	else
		rules->min_eat_nb = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philo);
	if (!rules->forks)
		return (EXIT_FAILURE);
	while (++i < rules->nb_of_philo)
		pthread_mutex_init(&rules->forks[i], NULL);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_rules			*rules;
	int				i;

	i = -1;
	if (parsing(ac, av))
		return (EXIT_FAILURE);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (EXIT_FAILURE);
	if (init_rules(rules, ac, av))
		return (EXIT_FAILURE);
	if (create_philos(rules))
		return (EXIT_FAILURE);
	while (++i < rules->nb_of_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	free(rules->forks);
	free(rules);
	return (EXIT_SUCCESS);
}
