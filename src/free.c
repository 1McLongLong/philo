/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:17:18 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:17:19 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->priv_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->main_lock);
	pthread_mutex_destroy(&data->message_lock);
}

void	free_all(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
	if (data->forks)
		free(data->forks);
	if (data->priv_lock)
		free(data->priv_lock);
	if (data)
		free(data);
}
