#include "header.h"


void	new_sleep(int mil_sec)
{
	long int	start_time;

	start_time = get_time_now();
	while ((get_time_now() - start_time) < mil_sec)
		usleep(100);
}


int	alive_check(t_data_philo *philo)
{
	pthread_mutex_lock(philo -> main_lock);
	if (!philo -> stop)
	{
		pthread_mutex_unlock(philo -> main_lock);
		return (1);
	}
	pthread_mutex_unlock(philo -> main_lock);
	return (0);
}

void	update_meal_status(t_data_philo *philo)
{
	pthread_mutex_lock(philo -> priv_lock);
	philo -> last_meal_time = get_time_now();
	pthread_mutex_unlock(philo -> priv_lock);
	if (philo->eat_x_times != 0)
	{
		if (++philo->ate_x_times == philo->eat_x_times)
		{
			pthread_mutex_lock(philo -> main_lock);
			*philo->already_ate_max += 1;
			pthread_mutex_unlock(philo -> main_lock);
		}
	}
}

int	meal(t_data_philo	*philo)
{
	if (!alive_check(philo))
		return (-1);
	pthread_mutex_lock(philo -> left_fork);
	print_info(philo, "has taken left fork");
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork), -1);
	if (philo -> right_fork == NULL)
		return (pthread_mutex_unlock(philo -> left_fork), new_sleep(philo -> time_to_die * 1.1), -1);
	pthread_mutex_lock(philo -> right_fork);
	print_info(philo, "has taken right fork");
	print_info(philo, "is eating");
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork), pthread_mutex_unlock(philo -> right_fork), -1);
	update_meal_status(philo);
	if (!alive_check(philo))
		return (pthread_mutex_unlock(philo -> left_fork), pthread_mutex_unlock(philo -> right_fork), -1);
	new_sleep(philo -> time_to_eat);
	pthread_mutex_unlock(philo -> right_fork);
	pthread_mutex_unlock(philo -> left_fork);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_data_philo	*philo;

	philo = (t_data_philo *)arg;
	if (philo->philo_id % 2 == 0)
		new_sleep(philo->time_to_eat * 0.9);
	while (alive_check(philo))
	{
		if (meal(philo) == -1)
			return (NULL);
		if (!alive_check(philo))
			return (NULL);
		print_info(philo, "is sleeping");
		new_sleep(philo -> time_to_sleep);
		print_info(philo, "is thinking");
	}
	return (NULL);
}
