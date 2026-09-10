/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:13:03 by echarmai          #+#    #+#             */
/*   Updated: 2026/09/10 18:10:11 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	stop_threads(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	data->ready = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

static void	join_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			while (i > 0)
				pthread_join(data->philos[--i].thread, NULL);
			return (0);
		}
		i++;
	}
	pthread_mutex_lock(&data->dead_lock);
	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i++].last_meal = data->start_time;
	}
	data->ready = 1;
	pthread_mutex_unlock(&data->dead_lock);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	data.ready = 0;
	if (!init_data(&data, argc, argv))
		return (1);
	if (!init_philos(&data))
		return (free_all(&data), 1);
	if (!start_threads(&data))
		return (free_all(&data), 1);
	check_death(&data);
	join_threads(&data, data.nb_philo);
	free_all(&data);
	return (0);
}

// GERER LE STOP_THREADS !!! (savoir ou le mettre)