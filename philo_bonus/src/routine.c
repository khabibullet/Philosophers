/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:59:05 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/25 12:33:02 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*death_monitor(void *tbl)
{
	long	current;
	t_table	*table;

	table = (t_table *)tbl;
	while (1)
	{
		current = get_sys_time();
		if (current - table->last_meal > table->inputs.time_to_die)
		{
			philo_notify(table, "died", 1);
			sem_post(table->sem_clean);
			return (NULL);
		}
		usleep(1000);
	}
}

int	feed_philo(t_table *table)
{
	sem_wait(table->sem_forks_up);
	sem_wait(table->sem_forks);
	philo_notify(table, "has taken a fork", 0);
	sem_wait(table->sem_forks);
	sem_post(table->sem_forks_up);
	table->last_meal = get_sys_time();
	philo_notify(table, "has taken a fork", 0);
	philo_notify(table, "is eating", 0);
	ft_usleep(table->inputs.time_to_eat);
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
	return (0);
}

int	start_dinner(t_table *table)
{
	int	eat_count;

	if (table->pid != 0)
		return (0);
	eat_count = 0;
	while (1)
	{
		feed_philo(table);
		eat_count++;
		if (eat_count == table->inputs.num_each_eat)
			sem_post(table->sem_fed);
		philo_notify(table, "is sleeping", 0);
		ft_usleep(table->inputs.time_to_sleep);
		philo_notify(table, "is thinking", 0);
	}
	return (0);
}

void	*fed_monitor(void *tbl)
{
	register int	i;
	t_table			*table;

	table = (t_table *)tbl;
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		sem_wait(table->sem_fed);
		i++;
	}
	sem_post(table->sem_clean);
	return (NULL);
}

int	full_clean(t_table *table)
{
	register int	i;

	if (table->pid == 0)
		return (0);
	sem_wait(table->sem_clean);
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		kill(table->cpids[i], SIGKILL);
		i++;
	}
	sem_post(table->sem_fed);
	sem_close(table->sem_forks);
	sem_close(table->sem_clean);
	sem_close(table->sem_fed);
	sem_close(table->sem_print);
	sem_close(table->sem_forks_up);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("all_fed");
	sem_unlink("forks_up");
	sem_unlink("clean_up");
	free(table->cpids);
	return (0);
}
