/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:48:35 by eloi              #+#    #+#             */
/*   Updated: 2026/09/10 14:45:48 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_dead(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	time_since_meal = get_time() - philo->last_meal;
	if (time_since_meal >= philo->data->time_to_die)
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", get_time() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

static int	check_all_eaten(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	pthread_mutex_lock(&data->dead_lock);
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished_eating++;
		i++;
	}
	if (finished_eating == data->nb_philo)
	{
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_simulation_ready(data))
		usleep(100);
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (check_all_eaten(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
