/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:13:27 by eloi              #+#    #+#             */
/*   Updated: 2026/08/04 10:25:53 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time, t_data *data)
{
	long	start;

	start = get_time();
	while (!is_simulation_dead(data))
	{
		if (get_time() - start >= time)
			break ;
		usleep(200);
	}
}
