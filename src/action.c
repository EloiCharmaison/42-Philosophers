/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_and_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:01:08 by marvin            #+#    #+#             */
/*   Updated: 2026/05/11 15:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n",
			get_time() - philo->data->start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
}

static void	take_fork(t_philo *philo)
{
//	if (data->nb_philo == 1)
//		return ;
//	if (is_simulation_dead(philo->data))
//		return ;
	if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo, t_data *data)
{
	if (is_simulation_dead(data))
		return ;
	if (data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken fork");
		ft_usleep(data->time_to_die, data);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_fork(philo);
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->dead_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->dead_lock);
	drop_forks(philo);
}

void	sleep_and_think(t_philo *philo)
{
	if (is_simulation_dead(philo->data))
		return ;
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
	if (is_simulation_dead(philo->data))
		return ;
	print_action(philo, "is thinking");
}
