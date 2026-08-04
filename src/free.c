/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:19:21 by eloi              #+#    #+#             */
/*   Updated: 2026/08/04 10:26:36 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data * data)
{
	int	i;

	if (data->fork)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		free(data->fork);
		data->fork = NULL;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
}
