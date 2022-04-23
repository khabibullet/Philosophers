/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:22:32 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/23 14:27:11 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_dinner(t_table *table)
{
	register int	i;

	table->start_time = get_sys_time();
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		pthread_create(&(table->philos[i].thread), NULL,
			(void *(*)(void *))eat_or_die, &table->philos[i]);
		i++;
	}
	pthread_mutex_lock(&table->print_lock);
	table->meal_end = 0;
	pthread_mutex_unlock(&table->print_lock);
	return (0);
}

int	end_dinner(t_table *table)
{
	register int	i;

	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->philos);
	free(table->forks);
	return (0);
}
