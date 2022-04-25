/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:36:02 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/25 12:33:00 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (init_inputs(argc, &argv, &table.inputs))
	{
		printf("Invalid input\n");
		return (1);
	}
	init_forks(&table, table.inputs.num_of_philos);
	init_philos(&table, table.inputs.num_of_philos);
	start_dinner(&table);
	end_dinner(&table);
	return (0);
}
