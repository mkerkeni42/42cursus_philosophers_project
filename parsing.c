/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:51:43 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/09 15:00:07 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_nb(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (arg[i] < '0' || arg[i] > '9')
		{
			write(2, "ERROR: numeric argument required !\n", 35);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	parsing(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		write(2, "ERROR: bad number of arguments !\n", 33);
		return (1);
	}
	while (++i < ac)
	{
		if (check_if_nb(av[i]))
			return (EXIT_FAILURE);
		if (ft_atol(av[i]) < 0)
		{
			write(2, "ERROR: positive argument required !\n", 36);
			return (EXIT_FAILURE);
		}
		if (ft_atol(av[i]) > INT_MAX)
		{
			write(2, "ERROR: argument too big !\n", 26);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
