/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/23 15:26:53 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_rules *rules, t_philo *philo, int i)
{
	philo[i].left_fork = &rules->forks[i];
	if (i == 0)
		philo[i].right_fork = &rules->forks[rules->nb_of_philo - 1];
	else
		philo[i].right_fork = &rules->forks[i - 1];
}

static int	create_philos(t_rules *rules)
{
	t_philo			*philo;
	pthread_t		death;
	int				i;

	i = -1;
	philo = malloc(sizeof(t_philo) * rules->nb_of_philo);
	while (++i < rules->nb_of_philo)
	{
		philo[i].eat_counter = 0;
		philo[i].last_meal = 0;
		philo[i].id = i + 1;
		philo[i].rules = rules;
		philo[i].start_time = get_time();
		get_forks(rules, philo, i);
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
			write(2, "Failed to create thread\n", 25);
	}
	pthread_create(&death, NULL, &death_handler, philo);
	if (pthread_join(death, NULL))
		write(2, "Failed to wait for the thread to finish\n", 41);
	free(philo);
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
	if (ac == 6)
		rules->min_eat_nb = ft_atol(av[5]);
	else
		rules->min_eat_nb = INT_MAX;
	pthread_mutex_init(&rules->printer, NULL);
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
	pthread_mutex_destroy(&rules->printer);
	free(rules->forks);
	free(rules);
	return (EXIT_SUCCESS);
}
