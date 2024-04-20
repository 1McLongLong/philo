/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:13:32 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:21:09 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_arg(t_data *data, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->eat_x_times = ft_atoi(argv[5]);
		if (data->eat_x_times < 0)
			printf("The number of meals cannot be negative\n");
	}
	else
		data->eat_x_times = 0;
}

int	check_errors(t_data *data)
{
	if (data->num_philos <= 0 || data->num_philos > 200)
		return (1);
	else if (data->time_to_die < 60)
		return (1);
	else if (data->time_to_eat < 60)
		return (1);
	else if (data->time_to_sleep < 60)
		return (1);
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("Wrong input\n"), 1);
	while (i < argc)
	{
		if (ft_isdigit(argv[i]))
			return (printf("Wrong input\n"), 1);
		if (check_range(argv[i]))
			return (printf("Wrong input\n"), 1);
		i++;
	}
	init_arg(data, argv);
	if (check_errors(data))
		return (printf("Wrong input\n"), free(data), 1);
	return (0);
}
