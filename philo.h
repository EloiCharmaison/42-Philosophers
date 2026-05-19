/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 12:00:18 by echarmai          #+#    #+#             */
/*   Updated: 2026/05/19 13:59:44 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				ready;
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	int				dead;
	long			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *nptr);
void	*check_death(void *arg);
int		init_philos(t_data *data);
int		init_data(t_data *data, int size, char **tab);
void	free_all(t_data *data);
long	get_time(void);
void	ft_usleep(long time);
int		main(int argc, char **argv);
void	eat(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	free_all(t_data *data);
void	*philo_routine(void *arg);
int		is_simulation_dead(t_data *data);
int		is_simulation_ready(t_data *data);

#endif