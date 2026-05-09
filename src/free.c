/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloi <eloi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:19:21 by eloi              #+#    #+#             */
/*   Updated: 2026/05/09 16:31:29 by eloi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data * data)
{
	int	i;

	i = 0;
	if (data->fork)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
		free(data->fork);
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->philos)
		free(data->philos);
}
