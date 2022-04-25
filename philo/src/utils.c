/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:55:54 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/23 16:11:28 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_sys_time(void)
{
	long			sys_time;
	struct timeval	tv1;

	gettimeofday(&tv1, NULL);
	sys_time = tv1.tv_usec / 1000 + tv1.tv_sec * 1000;
	return (sys_time);
}

int	ft_usleep(long time, t_philo *philo)
{
	long			start;
	long			sys_time;

	pthread_mutex_lock(philo->print_lock);
	if (*philo->meal_end == philo->inputs->num_of_philos)
	{
		pthread_mutex_unlock(philo->print_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->print_lock);
	sys_time = get_sys_time();
	start = sys_time;
	while (sys_time - start < time)
	{
		pthread_mutex_lock(philo->print_lock);
		if (*philo->meal_end == philo->inputs->num_of_philos)
		{
			pthread_mutex_unlock(philo->print_lock);
			return (0);
		}
		pthread_mutex_unlock(philo->print_lock);
		usleep(500);
		sys_time = get_sys_time();
	}
	return (0);
}

int	philo_notify(t_philo *philo, char *msg, int death)
{
	long	event;

	event = get_sys_time();
	pthread_mutex_lock(philo->print_lock);
	if (*philo->meal_end != philo->inputs->num_of_philos)
		printf("%ld %d %s\n", (event - *philo->start_time), philo->name, msg);
	if (death)
		*philo->meal_end = philo->inputs->num_of_philos;
	pthread_mutex_unlock(philo->print_lock);
	return (0);
}
