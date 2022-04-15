/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:55:54 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/15 19:07:15 by anemesis         ###   ########.fr       */
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
	sys_time = tv1.tv_usec + tv1.tv_sec * 1000000;
	start = sys_time;
	while (sys_time - start < time)
	{
		if (safe_getting_time(&tv1))
			return (1);
		sys_time = tv1.tv_usec + tv1.tv_sec * 1000000;
		if (usleep(500))
		{
			printf("Error calling usleep()\n");
			return (1);
		}
	}
	return (0);
}
