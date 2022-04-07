/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:04:38 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/07 19:15:34 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct t_input
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_each_eat;
}	t_input;

typedef struct t_philo
{
	int				name;
	int				left_fork;
	int				right_fork;
	long			*time_start;
	t_input			*inputs;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	int				*return_0;
	int				*return_1;
	int				*death;
	pthread_mutex_t	*only_print;
}	t_philo;

typedef struct t_table
{
	t_input			inputs;
	t_philo			*philos;
	long			time_start;
	pthread_mutex_t	*forks;
	int				return_0;
	int				return_1;
	int				*error;
	int				death;
	pthread_mutex_t	only_print;
}	t_table;

int	ft_atoi(const char	*str);

#endif
