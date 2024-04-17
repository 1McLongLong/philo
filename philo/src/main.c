#include "header.h"

int join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (parse_args(data, argc, argv))
		return (0);
	if (!init_data(data))
		return (EXIT_FAILURE);
	check_philos(data, data->philos);
	join_threads(data);
	free_mutex(data);
	free_all(data);
}
