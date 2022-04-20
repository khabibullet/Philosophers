/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:55:54 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/16 17:47:02 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	safe_malloc(void **ptr, size_t size, char *str)
{
	*ptr = malloc(size);
	if (!*ptr)
	{
		printf("%s\n", str);
		return (1);
	}
	return (0);
}

long	get_sys_time(void)
{
	long			sys_time;
	struct timeval	tv1;

	if (gettimeofday(&tv1, NULL))
	{
		printf("Error getting time\n");
		return (-1);
	}
	sys_time = tv1.tv_usec / 1000 + tv1.tv_sec * 1000;
	return (sys_time);
}

static int	safe_getting_time(struct timeval *tv1)
{
	if (gettimeofday(tv1, NULL))
	{
		printf("Error getting time\n");
		return (1);
	}
	return (0);
}

int	ft_usleep(long time, t_philo *philo)
{
	long			start;
	long			sys_time;
	struct timeval	tv1;

	if (philo != NULL && *philo->meal_end == philo->inputs->num_of_philos)
		return (0);
	if (safe_getting_time(&tv1))
		return (1);
	sys_time = tv1.tv_usec / 1000 + tv1.tv_sec * 1000;
	start = sys_time;
	while (sys_time - start < time)
	{
		if (usleep(500))
		{
			printf("Error calling usleep()\n");
			return (1);
		}
		if (safe_getting_time(&tv1))
			return (1);
		sys_time = tv1.tv_usec / 1000 + tv1.tv_sec * 1000;
	}
	return (0);
}

int	philo_notify(t_philo *philo, char *msg, int death)
{
	long	event;

	if (pthread_safe_mut_lock(philo->print_lock))
		return (1);
	event = get_sys_time();
	if (event == -1)
		return (1);
	if (*philo->meal_end != philo->inputs->num_of_philos)
		printf("%ld %d %s\n", (event - *philo->start_time), philo->name, msg);
	if (death)
		*philo->meal_end = philo->inputs->num_of_philos;
	if (pthread_safe_mut_unlock(philo->print_lock))
		return (1);
	return (0);
}
