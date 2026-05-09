/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloi <eloi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:48:35 by eloi              #+#    #+#             */
/*   Updated: 2026/05/09 16:51:46 by eloi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_dead(t_philo * philo)
{
	long	time_since_meal;

	time_since_meal = get_time() - philo->last_meal;
	if (time_since_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->print);
		print("%ld %d died\n");
			get_time() - philo->data->start_time;
			philo->id;
		pthread_mutex_unlock(&philo->data->print);
		return (0);
	}
	return (1);
}

int	check_death(t_data * data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philos[i]))
				return (0);
			i++;
		}
		usleep(1000);
	}
	return (1);
}
