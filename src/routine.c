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

static void precise_sleep(long time, t_data *data)
{
	long	start_time;

	start_time = get_time();
	while (!is_simulation_dead(data))
	{
		if (get_time() - start_time >= time)
			break ;
		usleep(200);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_ready(philo->data))
		usleep(100);
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!is_simulation_dead(philo->data))
	{
		eat(philo, philo->data);
		if (is_simulation_dead(philo->data))
			break ;
		print_action(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep, philo->data);
		if (is_simulation_dead(philo->data))
			break ;
		print_action(philo, "is thinking");
		precise_sleep(1, philo->data);
	}
	return (NULL);
}
