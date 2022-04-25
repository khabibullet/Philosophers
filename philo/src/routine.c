/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:22:32 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/25 12:32:59 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	start_dinner(t_table *table)
{
	register int	i;

	table->start_time = get_sys_time();
	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		pthread_create(&(table->philos[i].thread), NULL,
			(void *(*)(void *))eat_or_die, &table->philos[i]);
		i++;
	}
	pthread_mutex_lock(&table->print_lock);
	table->meal_end = 0;
	pthread_mutex_unlock(&table->print_lock);
	return (0);
}

int	end_dinner(t_table *table)
{
	register int	i;

	i = 0;
	while (i < table->inputs.num_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		pthread_mutex_unlock(&table->forks[i]);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->philos);
	free(table->forks);
	return (0);
}

void	*death_monitor(void *arg)
{
	long	current;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->print_lock);
		if (*philo->meal_end == philo->inputs->num_of_philos)
		{
			pthread_mutex_unlock(philo->print_lock);
			break ;
		}
		pthread_mutex_unlock(philo->print_lock);
		current = get_sys_time();
		pthread_mutex_lock(&philo->last_meal_lock);
		if (current - philo->last_meal > philo->inputs->time_to_die)
		{
			pthread_mutex_unlock(&philo->last_meal_lock);
			philo_notify(philo, "died", 1);
			break ;
		}
		pthread_mutex_unlock(&philo->last_meal_lock);
		ft_usleep(1, philo);
	}
	return (NULL);
}

int	eat_sleep_repeat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_notify(philo, "has taken a fork", 0);
	if (philo->inputs->num_of_philos == 1)
		return (1);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_sys_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
	philo_notify(philo, "has taken a fork", 0);
	philo_notify(philo, "is eating", 0);
	ft_usleep(philo->inputs->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_count++;
	pthread_mutex_lock(philo->print_lock);
	if (philo->eat_count == philo->inputs->num_each_eat)
		*philo->meal_end += 1;
	pthread_mutex_unlock(philo->print_lock);
	philo_notify(philo, "is sleeping", 0);
	ft_usleep(philo->inputs->time_to_sleep, philo);
	philo_notify(philo, "is thinking", 0);
	return (0);
}

void	*eat_or_die(t_philo *philo)
{
	pthread_mutex_init(&philo->last_meal_lock, NULL);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = *philo->start_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	pthread_create(&philo->death_check, NULL, &death_monitor, philo);
	if (philo->name % 2)
		usleep(1000);
	philo->eat_count = 0;
	while (1)
	{
		pthread_mutex_lock(philo->print_lock);
		if (*philo->meal_end == philo->inputs->num_of_philos)
		{
			pthread_mutex_unlock(philo->print_lock);
			break ;
		}
		pthread_mutex_unlock(philo->print_lock);
		if (eat_sleep_repeat(philo))
			break ;
	}
	pthread_join(philo->death_check, NULL);
	pthread_mutex_destroy(&philo->last_meal_lock);
	return (NULL);
}
