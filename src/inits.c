/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:12:21 by eloi              #+#    #+#             */
/*   Updated: 2026/09/08 14:11:35 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_partial_mutexes(t_data *data, int count)
{
	int	i;

	if (!data->fork)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	data->fork = NULL;
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			free_partial_mutexes(data, i);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (free_partial_mutexes(data, data->nb_philo), 0);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		free_partial_mutexes(data, data->nb_philo);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, int size, char **tab)
{
	data->nb_philo = ft_atoi(tab[1]);
	data->time_to_die = ft_atoi(tab[2]);
	data->time_to_eat = ft_atoi(tab[3]);
	data->time_to_sleep = ft_atoi(tab[4]);
	data->must_eat = -1;
	if (size == 6)
		data->must_eat = ft_atoi(tab[5]);
	data->dead = 0;
	data->ready = 0;
	data->all_eaten = 0;
	data->start_time = 0;
	data->philos = NULL;
	data->fork = NULL;
	if (data->nb_philo <= 0
		|| data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (0);
	if (size == 6 && data->must_eat <= 0)
		return (0);
	if (!init_mutexes(data))
		return (0);
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		i++;
	}
	return (1);
}
