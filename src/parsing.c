#include "header.h"

int	check_error(t_table *table)
{
	if (table -> philos_num < 1)
		return (printf("Wrong input\n"), 0);
	if (table -> time_to_die <= 0)
		return (printf("Wrong input\n"), 0);
	if (table -> time_to_eat <= 0)
		return (printf("Wrong input\n"), 0);
	if (table -> time_to_sleep <= 0)
		return (printf("Wrong input\n"), 0);
	return (1);
}

void	set_arguments(t_table *table, int argc, char **argv)
{	
	table->philos_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		table -> eat_x_times = ft_atoi(argv[5]);
		if (argv[5] && table -> eat_x_times < 0)
			printf("The number of meals cannot be negative\n");
	}
	else
		table -> eat_x_times = 0;
}

int	parse_args(t_table *table, int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (printf("Wrong input\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (!ft_isdigit(argv[i]))
			return (printf("Wrong input\n"), 0);
		if (check_range(argv[i]) <= 0)
			return (printf("Wrong input\n"), 0);
		i++;
	}
	set_arguments(table, argc, argv);
	if (check_error(table) == 0)
		return (free(table), 0);
	return (1);
}
