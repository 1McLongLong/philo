/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:21:38 by touahman          #+#    #+#             */
/*   Updated: 2024/04/19 10:21:52 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_info(t_data_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(philo->message_lock);
	time = get_time_now() - *philo->start_time;
	if (time >= 0 && time <= 2147483647 && alive_check(philo))
		printf("%d %d %s\n", (int)time, philo->philo_id, str);
	pthread_mutex_unlock(philo -> message_lock);
}

int	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
