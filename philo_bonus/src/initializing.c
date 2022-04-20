/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:01:04 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/20 16:39:22 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_inputs(int argc, char ***argv, t_input *inputs)
{
	if (argc != 5 && argc != 6)
	{
		printf("Invalid input. Wrong number of arguments\n");
		return (1);
	}
	inputs->num_of_philos = ft_atoi((*argv)[1]);
	if (inputs->num_of_philos > 200 || inputs->num_of_philos < 1)
	{
		printf("Invalid input. Wrong number of philosophers\n");
		return (1);
	}
	inputs->time_to_die = ft_atoi((*argv)[2]);
	inputs->time_to_eat = ft_atoi((*argv)[3]);
	inputs->time_to_sleep = ft_atoi((*argv)[4]);
	if (inputs->time_to_die < 60 || inputs->time_to_eat < 60
		|| inputs->time_to_sleep < 60)
	{
		printf("Invalid input. Need more time to die/eat/sleep\n");
		return (1);
	}
	if (argc == 6)
		inputs->num_each_eat = ft_atoi((*argv)[5]);
	else
		inputs->num_each_eat = -1;
	return (0);
}

int	init_philos(t_table *table)
{
	register int	i;

	table->cpids = malloc(sizeof(*table->cpids) * table->inputs.num_of_philos);
	if (!table->cpids)
		return (1);
	table->start_time = get_sys_time();
	if (table->start_time == -1)
		return (1);
	table->last_meal = table->start_time;
	if (table->start_time == -1)
		return (1);
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		table->pid = fork();
		ft_usleep(1);
		if (table->pid == -1)
			return (1);
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
	table->sem_forks = sem_open("forks", O_CREAT | O_EXCL, 0644, num_of_philos);
	table->sem_print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	table->sem_clean = sem_open("clean_up", O_CREAT | O_EXCL, 0644, 0);
	table->sem_fed = sem_open("all_fed", O_CREAT | O_EXCL, 0644, 0);
	return (0);
}

int	init_monitors(t_table *table)
{
	if (table->pid != 0)
	{
		if (pthread_safe_create(&table->monitor, &fed_monitor, (void *)table))
			return (1);
		if (pthread_safe_detach(table->monitor))
			return (1);
		return (0);
	}
	if (pthread_safe_create(&table->monitor, &death_monitor, (void *)table))
		return (1);
	if (pthread_safe_detach(table->monitor))
		return (1);
	return (0);
}
