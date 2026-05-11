/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:29:48 by marvin            #+#    #+#             */
/*   Updated: 2026/05/11 14:29:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_simulation_dead(t_data * data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_dead(philo->data))
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
