/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:57:11 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/19 15:22:50 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	pthread_safe_mut_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
	{
		printf("Error while destroying mutex\n");
		return (1);
	}
	return (0);
}

int	pthread_safe_mut_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		printf("Error while locking mutex\n");
		return (1);
	}
	return (0);
}

int	pthread_safe_mut_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
	{
		printf("Error while unlocking mutex\n");
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

int	pthread_safe_join(pthread_t thread)
{
	if (pthread_join(thread, NULL))
	{
		printf("Error while joining thread\n");
		return (1);
	}
	return (0);
}
