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
	if (is_simulation_dead(philo->data))
		return (NULL);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (!is_simulation_dead(philo->data))
	{
		eat(philo, philo->data);
		if (is_simulation_dead(philo->data))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
