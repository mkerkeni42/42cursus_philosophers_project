/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/12 11:40:45 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_forks(t_rules *rules, t_philo *philo, int i)
{
	philo[i].right_fork = NULL;
	pthread_mutex_init(&philo[i].left_fork, NULL);
	if (rules->nb_of_philo == 1)
		philo[i].right_fork = NULL;
	else if (i == rules->nb_of_philo - 1)
		philo[i].right_fork = &philo[0].left_fork;
	else
		philo[i].right_fork = &philo[i + 1].left_fork;
}

static void	wait_for_threads(t_philo *philo, t_rules *rules, pthread_t *death)
{
	int	i;

	i = -1;
	while (++i < rules->nb_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			write(2, "Failed to wait for the thread to finish\n", 41);
	}
	if (pthread_join(*death, NULL))
		write(2, "Failed to wait for the thread to finish\n", 41);
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
		philo[i].last_meal = get_time();
		philo[i].id = i + 1;
		philo[i].rules = rules;
		pthread_mutex_init(&philo[i].counter_access, NULL);
		pthread_mutex_init(&philo[i].meal_access, NULL);
		get_forks(rules, philo, i);
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
			write(2, "Failed to create thread\n", 25);
	}
	if (pthread_create(&death, NULL, &death_handler, philo))
		write(2, "Failed to create thread\n", 25);
	wait_for_threads(philo, rules, &death);
	free_mutexes(rules, philo);
	return (0);
}

static int	init_rules(t_rules *rules, int ac, char **av)
{
	rules->start_time = get_time();
	rules->death_signal = 0;
	rules->nb_of_philo = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		rules->min_eat_nb = ft_atol(av[5]);
	else
		rules->min_eat_nb = -1;
	pthread_mutex_init(&rules->printer, NULL);
	pthread_mutex_init(&rules->death_access, NULL);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_rules			*rules;

	if (parsing(ac, av))
		return (EXIT_FAILURE);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (EXIT_FAILURE);
	if (init_rules(rules, ac, av))
		return (EXIT_FAILURE);
	if (create_philos(rules))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
