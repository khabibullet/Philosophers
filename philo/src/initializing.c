/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:01:04 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/23 16:38:15 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_inputs(int argc, char ***argv, t_input *inputs)
{
	if (argc != 5 && argc != 6)
		return (1);
	inputs->num_of_philos = ft_atoi((*argv)[1]);
	if (inputs->num_of_philos > 200 || inputs->num_of_philos < 1)
		return (1);
	inputs->time_to_die = ft_atoi((*argv)[2]);
	inputs->time_to_eat = ft_atoi((*argv)[3]);
	inputs->time_to_sleep = ft_atoi((*argv)[4]);
	if (inputs->time_to_die < 60 || inputs->time_to_eat < 60
		|| inputs->time_to_sleep < 60)
		return (1);
	if (argc == 6)
		inputs->num_each_eat = ft_atoi((*argv)[5]);
	else
		inputs->num_each_eat = -1;
	if (!inputs->num_each_eat)
		return (1);
	return (0);
}

int	init_philos(t_table *table, int num_of_philos)
{
	register int	i;

	table->philos = malloc(sizeof(*(table->philos)) * num_of_philos);
	table->meal_end = 0;
	i = 0;
	while (i < num_of_philos)
	{
		(table->philos)[i].name = i;
		(table->philos)[i].meal_end = &table->meal_end;
		(table->philos)[i].print_lock = &table->print_lock;
		(table->philos)[i].inputs = &table->inputs;
		(table->philos)[i].start_time = &table->start_time;
		(table->philos)[i].left_fork = &table->forks[i];
		if (i == table->inputs.num_of_philos - 1)
			(table->philos)[i].right_fork = &table->forks[0];
		else
			(table->philos)[i].right_fork = &table->forks[i + 1];
		i++;
	}
	return (0);
}

int	init_forks(t_table *table, int num_of_philos)
{
	register int	i;

	table->forks = malloc(sizeof(*table->forks) * num_of_philos);
	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_init(&((table->forks)[i]), NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	return (0);
}
