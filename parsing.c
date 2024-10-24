/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:51:43 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/12/07 15:55:21 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_nb(char *arg)
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

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	check_if_valid_nb(char *arg)
{
	long	nb;

	if (ft_strlen(arg) > 10)
	{
		write(2, "ERROR: argument too big !\n", 26);
		return (EXIT_FAILURE);
	}
	nb = ft_atol(arg);
	if (nb < 0)
	{
		write(2, "ERROR: positive argument required !\n", 36);
		return (EXIT_FAILURE);
	}
	if (nb > INT_MAX)
	{
		write(2, "ERROR: argument too big !\n", 26);
		return (EXIT_FAILURE);
	}
	if (nb == 0)
	{
		write(2, "ERROR: argument cannot be zero !\n", 33);
		return (EXIT_FAILURE);
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
		return (EXIT_FAILURE);
	}
	while (++i < ac)
	{
		if (check_if_nb(av[i]))
			return (EXIT_FAILURE);
		if (check_if_valid_nb(av[i]))
			return (EXIT_FAILURE);
	}
	if (ft_atol(av[1]) > 200)
	{
		write(2, "ERROR: more than 200 philosophers not allowed !\n", 48);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
