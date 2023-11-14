/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:28:48 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/14 15:30:47 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(struct timeval *cmp_time)
{
	struct timeval	tv;
	long long		elapsed_time;

	gettimeofday(&tv, NULL);
	elapsed_time = (((tv.tv_sec * 1000) - (cmp_time->tv_sec * 1000)) + \
	((tv.tv_usec / 1000) - (cmp_time->tv_usec / 1000)));
	return (elapsed_time);
}
