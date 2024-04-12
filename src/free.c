#include "header.h"

void	destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table -> philos_num)
	{
		pthread_mutex_destroy(&table -> forks[i]);
		pthread_mutex_destroy(&table -> priv_lock[i]);
	}
	pthread_mutex_destroy(&table -> main_lock);
	pthread_mutex_destroy(&table -> write_message);
}

void	free_all(t_table *table)
{
	if (table->threads)
		free(table->threads);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	if (table->priv_lock)
		free(table->priv_lock);
	if (table)
		free(table);
}
