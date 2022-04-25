/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:01:04 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/25 11:46:57 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

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

int	init_philos(t_table *table)
{
	register int	i;

	table->cpids = malloc(sizeof(*table->cpids) * table->inputs.num_of_philos);
	table->start_time = get_sys_time();
	table->last_meal = table->start_time;
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		table->pid = fork();
		if (table->pid == 0)
			break ;
		table->cpids[i] = table->pid;
		i++;
	}
	table->philo_name = i;
	return (0);
}

int	init_forks(t_table *table, int num_of_philos)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("all_fed");
	sem_unlink("forks_up");
	sem_unlink("clean_up");
	table->sem_forks = sem_open("forks", O_CREAT | O_EXCL, 0644, num_of_philos);
	table->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	table->sem_clean = sem_open("clean_up", O_CREAT | O_EXCL, 0644, 0);
	table->sem_fed = sem_open("all_fed", O_CREAT | O_EXCL, 0644, 0);
	table->sem_forks_up = sem_open("forks_up", O_CREAT | O_EXCL, 0644,
			num_of_philos / 2 + 1);
	return (0);
}

int	init_monitors(t_table *table)
{
	if (table->pid == 0)
	{
		pthread_create(&table->monitor, NULL, &death_monitor, table);
		pthread_detach(table->monitor);
	}
	else
	{
		pthread_create(&table->monitor, NULL, &fed_monitor, table);
		pthread_detach(table->monitor);
	}
	return (0);
}
