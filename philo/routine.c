/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:16:42 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:21:22 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_meal(t_data_philo *philo)
{
	pthread_mutex_lock(philo->priv_lock);
	philo->last_meal_time = get_time_now();
	if (philo->eat_x_times != 0)
	{
		if (++philo->ate_x_times == philo->eat_x_times)
		{
			pthread_mutex_lock(philo->main_lock);
			*philo->already_ate_max += 1;
			pthread_mutex_unlock(philo->main_lock);
		}
	}
	pthread_mutex_unlock(philo->priv_lock);
}

int	meal(t_data_philo *philo)
{
	if (!alive_check(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	print_info(philo, "has taken a fork");
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo->left_fork), 0);
	if (!philo->right_fork)
		return (pthread_mutex_unlock(philo->left_fork),
			ft_sleep(philo->time_to_die * 1.1), 0);
	pthread_mutex_lock(philo->right_fork);
	print_info(philo, "has taken a fork");
	if (philo->eat_x_times != 0)
		print_info(philo, "is eating");
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	update_meal(philo);
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 0);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	alive_check(t_data_philo *philo)
{
	pthread_mutex_lock(philo->main_lock);
	if (!philo->stop)
	{
		pthread_mutex_unlock(philo->main_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->main_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_data_philo	*philo;

	philo = (t_data_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_sleep(philo->time_to_eat * 0.9);
	while (alive_check(philo))
	{
		if (!meal(philo))
			return (NULL);
		if (!alive_check(philo))
			return (NULL);
		print_info(philo, "is sleeping");
		ft_sleep(philo->time_to_sleep);
		print_info(philo, "is thinking");
	}
	return (NULL);
}
