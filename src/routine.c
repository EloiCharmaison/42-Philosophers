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

int	is_simulation_ready(t_data *data)
{
	int	ready;

	pthread_mutex_lock(&data->dead_lock);
	ready = data->ready;
	pthread_mutex_unlock(&data->dead_lock);
	return (ready);
}

int	is_simulation_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_lock);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (dead);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_ready(philo->data))
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!is_simulation_dead(philo->data))
	{
		eat(philo);
		if (is_simulation_dead(philo->data))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
