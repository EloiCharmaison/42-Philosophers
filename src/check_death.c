/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 16:48:35 by eloi              #+#    #+#             */
/*   Updated: 2026/06/08 14:19:11 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_dead(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->dead_lock);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (time_since_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", get_time() - philo->data->start_time,
			philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (is_dead(&data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
