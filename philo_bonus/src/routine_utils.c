/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:55:54 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/22 20:56:49 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

long	get_sys_time(void)
{
	struct timeval	tv1;

	if (gettimeofday(&tv1, NULL))
	{
		printf("Error getting time\n");
		return (-1);
	}
	return (tv1.tv_usec / 1000 + tv1.tv_sec * 1000);
}

int	ft_usleep(long time)
{
	long	start;
	long	sys_time;

	sys_time = get_sys_time();
	if (sys_time == -1)
		return (1);
	start = sys_time;
	while (sys_time - start < time)
	{
		if (usleep(500))
		{
			printf("Error calling usleep()\n");
			return (1);
		}
		sys_time = get_sys_time();
		if (sys_time == -1)
			return (1);
	}
	return (0);
}

int	philo_notify(t_table *table, char *msg, int death)
{
	long	event;

	event = get_sys_time();
	if (event == -1)
		return (1);
	sem_wait(table->sem_print);
	printf("%ld %d %s\n", (event - table->start_time), table->philo_name, msg);
	if (!death)
		sem_post(table->sem_print);
	return (0);
}
