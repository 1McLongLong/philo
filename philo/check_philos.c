/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:15:48 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:15:49 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	meal_check(t_data *data, t_data_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->main_lock);
	if (data->already_ate_max == data->num_philos)
	{
		while (i < data->num_philos)
		{
			philo[i].stop = 1;
			i++;
		}
		pthread_mutex_unlock(&data->main_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->main_lock);
	return (0);
}

void	check_philos(t_data *data, t_data_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->priv_lock[i]);
		if (get_time_now() - philo[i].last_meal_time >= data->time_to_die)
		{
			pthread_mutex_unlock(&data->priv_lock[i]);
			pthread_mutex_lock(&data->main_lock);
			printf("%d %d died\n", (int)(get_time_now() - data->start_time),
				i + 1);
			i = -1;
			while (++i < data->num_philos)
				philo[i].stop = 1;
			pthread_mutex_unlock(&data->main_lock);
			return ;
		}
		pthread_mutex_unlock(&data->priv_lock[i]);
		if (meal_check(data, philo))
			return ;
		if (i + 1 == data->num_philos)
			i = -1;
	}
}
