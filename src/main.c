#include "header.h"

int	wait_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos_num)
		pthread_join(table->threads[i], NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (parse_args(table, argc, argv) == 0)
		return (0);
	if (init_data(table) == -1)
		return (EXIT_FAILURE);
	control(table, table -> philos);
	wait_threads(table);
	destroy(table);
	free_all(table);
}
