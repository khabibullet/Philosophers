/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:55:54 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/14 21:02:02 by anemesis         ###   ########.fr       */
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

int	pthread_safe_mut_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		printf("Error while initializing mutex\n");
		return (1);
	}
	return (0);
}

int	pthread_safe_mut_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
	{
		printf("Error while destroying mutex\n");
		return (1);
	}
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
		printf("Thread error\n");
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

void	ft_usleep(long time)
{
	long			start;
	long			sys_time;
	struct timeval	tv1;

	gettimeofday(&tv1, NULL);
	sys_time = tv1.tv_usec + tv1.tv_sec * 1000000;
	start = sys_time;
	while (sys_time - start < time)
	{
		gettimeofday(&tv1, NULL);
		sys_time = tv1.tv_usec + tv1.tv_sec * 1000000;
		usleep(500);
	}
}

int	philo_notify(long *start_time, t_philo *philo, char *msg)
{
	long	event_time;

	pthread_mutex_lock(philo->print_lock);
	event_time = get_sys_time();
	if (*philo->meal_end != philo->inputs->num_of_philos)
		printf("%ld %d %s\n", (event_time - *start_time), philo->name, msg);
	pthread_mutex_unlock(philo->print_lock);
	return (0);
}
