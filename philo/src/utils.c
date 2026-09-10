/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echarmai <echarmai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 15:34:49 by eloi              #+#    #+#             */
/*   Updated: 2026/09/10 18:02:30 by echarmai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	is_valid_number(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	long	res;
	int		i;

	if (!nptr || !is_valid_number(nptr))
		return (-1);
	res = 0;
	i = 0;
	while (nptr[i])
	{
		res = res * 10 + (nptr[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}
