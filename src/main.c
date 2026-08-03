/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:13:03 by echarmai          #+#    #+#             */
/*   Updated: 2026/08/03 13:10:53 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	pthread_mutex_lock(&data->dead_lock);
	data->start_time = get_time();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	data->ready = 1;
	pthread_mutex_unlock(&data->dead_lock);
	if (pthread_create(&data->philos[0].thread, NULL, check_death, data) != 0)
		return (0);
	return (1);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	//pthread_t	monitor;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers ");
		printf("time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	data.ready = 0;
	if (!init_data(&data, argc, argv))
		return (0);
	if (!init_philos(&data))
		return (free_all(&data), 0);
	data.start_time = get_time();
	data.ready = 1;
	if (!start_threads(&data))
		return (free_all(&data), 0);
	check_death(&data);
	//pthread_create(&monitor, NULL, check_death, &data);
	join_threads(&data);
	//pthread_join(monitor, NULL);
	free_all(&data);
	return (1);
}
