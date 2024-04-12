#include "header.h"


int	meal_control(t_table *table, t_data_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table -> main_lock);
	if (table->already_ate_max == table->philos_num)
	{
		printf("Is done eating\n");
		while (++i < table -> philos_num)
			philo[i].stop = 1;
		pthread_mutex_unlock(&table->main_lock);
		return (-1);
	}
	pthread_mutex_unlock(&table->main_lock);
	return (0);
}

void	control(t_table *table, t_data_philo *philo)
{
	int				i;

	i = -1;
	while (++i < table->philos_num)
	{
		pthread_mutex_lock(&table -> priv_lock[i]);
		if (get_time_now() - philo[i].last_meal_time >= table->time_to_die)
		{
			pthread_mutex_unlock(&table -> priv_lock[i]);
			pthread_mutex_lock(&table -> main_lock);
			printf("[%d] Philo: %d is dead\n", (int)(get_time_now() - table->start_time), i + 1);
			i = -1;
			while (++i < table->philos_num)
				philo[i].stop = 1;
			pthread_mutex_unlock(&table->main_lock);
			return ;
		}
		pthread_mutex_unlock(&table->priv_lock[i]);
		if (meal_control(table, philo) == -1)
			return ;
		if (i + 1 == table -> philos_num)
			i = -1;
	}
}
