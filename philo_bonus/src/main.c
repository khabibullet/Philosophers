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

#include "../inc/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (init_inputs(argc, &argv, &table.inputs))
	{
		printf("Invalid input\n");
		return (1);
	}
	init_forks(&table, table.inputs.num_of_philos);
	init_philos(&table);
	init_monitors(&table);
	start_dinner(&table);
	full_clean(&table);
	return (0);
}
