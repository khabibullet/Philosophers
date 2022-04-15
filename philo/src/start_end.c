/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:22:32 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/15 19:38:08 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_dinner(t_table *table)
{
	register int	i;

	table->start_time = get_sys_time();
	if (table->start_time == -1)
		return (1);
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		if (pthread_safe_create(&(table->philos[i].thread),
				(void *(*)(void *))eat_or_die, &table->philos[i]))
			return (1);
		i++;
	}
	if (pthread_safe_mut_lock(&table->end_lock))
		return (1);
	table->meal_end = 0;
	return (0);
}

int	end_dinner(t_table *table)
{
	register int	i;

	if (pthread_safe_mut_lock(&table->end_lock))
		return (1);
	if (pthread_safe_mut_unlock(&table->end_lock)){
		printf("8\n");
		return (1);
	}
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
		if (pthread_safe_mut_unlock(&table->forks[i])){
			printf("7\n");
			return (1);
		}
		if (pthread_safe_mut_destroy(&table->forks[i])){
			printf("here %d\n", i);
			perror(NULL);
			return (1);
		}
		i++;
	}
	if (pthread_safe_mut_destroy(&table->print_lock))
		return (1);
	if (pthread_safe_mut_destroy(&table->end_lock))
		return (1);
	free(table->philos);
	free(table->forks);
	return (0);
}

int	pthread_safe_create(pthread_t *thread, void *(*f)(void *), void *philo)
{
	if (pthread_create(thread, NULL, f, philo))
	{
		printf("Error. Cannot create thread\n");
		return (1);
	}
	return (0);
}

int	pthread_safe_detach(pthread_t thread)
{
	if (pthread_detach(thread))
	{
		printf("Error while detaching thread\n");
		return (1);
	}
	return (0);
}

int	pthread_safe_mut_join(pthread_t thread)
{
	if (pthread_join(thread, NULL))
	{
		printf("Error while joining thread\n");
		return (1);
	}
	return (0);
}
