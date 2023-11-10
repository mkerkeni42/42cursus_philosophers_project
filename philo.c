/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/10 15:54:50 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log_message(char *message, int id)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%ld %d %s\n", timestamp, id, message);
}

static void	*philo_life(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	
	while (1)
	{
		log_message("is thinking", philo->id);
		usleep(1000000);
		//pthread_mutex_lock(&philo->forks[philo->id]);
		//pthread_mutex_lock(&philo->forks[(philo->id + 1) % philo->rules->nb_of_philo]);
		log_message("has taken a fork", philo->id);
		log_message("is eating", philo->id);
		usleep(1000000);
		//pthread_mutex_unlock(&philo->forks[philo->id]);
		//pthread_mutex_unlock(&philo->forks[(philo->id + 1) % philo->rules->nb_of_philo]);
		log_message("is sleeping", philo->id);
		usleep(1000000);
	}
	return (NULL);
}

static int	create_philos(t_rules *rules, pthread_mutex_t *forks)
{
	t_philo			*philo;
	int			i;

	i = -1;
	philo = malloc(sizeof(t_philo));
	while (++i < rules->nb_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].rules = rules;
		philo[i].forks = forks;
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

static void	init_rules(t_rules *rules, int ac, char **av)
{
	rules->nb_of_philo = ft_atol(av[1]);
	rules->time_to_die = ft_atol(av[2]);
	rules->time_to_eat = ft_atol(av[3]);
	rules->time_to_sleep = ft_atol(av[4]);
	rules->eat_counter = 0;
	if (ac == 6)
		rules->min_eat_nb = ft_atol(av[5]);
	else
		rules->min_eat_nb = 0;
}

int	main(int ac, char **av)
{
	t_rules			*rules;
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	if (parsing(ac, av))
		return (EXIT_FAILURE);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (EXIT_FAILURE);
	init_rules(rules, ac, av);
	forks = malloc(sizeof(pthread_mutex_t) * rules->nb_of_philo);
	if (!forks)
		return (EXIT_FAILURE);
	while (++i < rules->nb_of_philo)
		pthread_mutex_init(&forks[i], NULL);
	if (create_philos(rules, forks))
		return (EXIT_FAILURE);
	i = -1;
	while (++i < rules->nb_of_philo)
		pthread_mutex_destroy(&forks[i]);
	return (EXIT_SUCCESS);
}
