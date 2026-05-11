/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:13:03 by echarmai          #+#    #+#             */
/*   Updated: 2026/05/11 16:01:09 by marvin           ###   ########.fr       */
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
	return (1);
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!init_data(&data, argc, argv))
		return (0);
	if (!init_philos(&data))
		return(free_all(&data), 0);
	data.start_time = get_time();
	if (!start_threads(&data))
		return (free_all(&data), 0);
	check_death(&data);
	join_threads(&data);
	free_all(&data);
	return (1);
}
