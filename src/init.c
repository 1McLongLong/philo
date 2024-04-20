/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:14:29 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:20:39 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_now();
	while (i < data->num_philos)
	{
		pthread_create(&data->threads[i], NULL, &routine, &data->philos[i]);
		i++;
	}
	return (1);
}

void	init_philos(t_data *data, t_data_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].eat_x_times = data->eat_x_times;
		philo[i].ate_x_times = 0;
		philo[i].already_ate_max = &data->already_ate_max;
		philo[i].last_meal_time = get_time_now();
		philo[i].start_time = &data->start_time;
		philo[i].stop = 0;
		philo[i].left_fork = &data->forks[i];
		if (data->num_philos > 1)
			philo[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		else
			philo[i].right_fork = NULL;
		philo[i].main_lock = &data->main_lock;
		philo[i].priv_lock = &data->priv_lock[i];
		philo[i].message_lock = &data->message_lock;
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free_all(data), 0);
	data->priv_lock = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->priv_lock)
		return (free_all(data), 0);
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->priv_lock[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->main_lock, NULL);
	pthread_mutex_init(&data->message_lock, NULL);
	return (1);
}

int	init_data(t_data *data)
{
	data->philos = malloc(sizeof(t_data_philo) * data->num_philos);
	if (!data->philos)
		return (free_all(data), 0);
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		return (free_all(data), 0);
	if (!init_mutex(data))
		return (0);
	data->already_ate_max = 0;
	init_philos(data, data->philos);
	init_threads(data);
	return (1);
}
