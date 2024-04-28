/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:13:00 by touahman          #+#    #+#             */
/*   Updated: 2024/04/18 10:20:51 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->threads[i], NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (parse_args(data, argc, argv))
		return (free(data), 0);
	if (!init_data(data))
		return (0);
	check_philos(data, data->philos);
	join_threads(data);
	free_mutex(data);
	free_all(data);
}
