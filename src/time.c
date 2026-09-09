/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:13:27 by eloi              #+#    #+#             */
/*   Updated: 2026/09/09 22:33:32 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000L) + tv.tv_usec);
}

void	ft_usleep(long time_in_ms, t_data *data)
{
	long	start_us;

	start_us = get_time_us();
	while ((get_time_us() - start_us) < (time_in_ms * 1000))
	{
		if (is_simulation_dead(data))
			break ;
		usleep(100);
	}
}
