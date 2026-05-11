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

static void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (!philo->data->dead)
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->dead_lock);
}

void	eat(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken fork");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_fork(philo);
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->dead_lock);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	release_forks(philo);




	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken fork");
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->dead_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		
	}
}

void	sleep_and_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	print_action(philo, "is thinking");
}
