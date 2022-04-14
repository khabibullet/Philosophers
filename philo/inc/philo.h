/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:04:38 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/14 20:55:32 by anemesis         ###   ########.fr       */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*end_lock;
	pthread_mutex_t	*time_lock;
	pthread_t		thread;
	pthread_t		death_check;
	t_input			*inputs;
	long			*start_time;
	long			last_meal;
	int				eat_count;
	int				*meal_end;

}	t_philo;

typedef struct t_table
{
	t_input			inputs;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	time_lock;
	int				meal_end;
	long			start_time;
}	t_table;

int		ft_atoi(const char	*str);

long	get_sys_time(void);
int		pthread_safe_mut_init(pthread_mutex_t *mutex);
int		pthread_safe_mut_destroy(pthread_mutex_t *mutex);
int		pthread_safe_create(pthread_t *thread, void *(*f)(void *), void *philo);
int		pthread_safe_detach(pthread_t thread);

int		init_inputs(int argc, char ***argv, t_input *inputs);
int		init_philos(t_table *table);
int		init_forks(t_table *table, int num_of_philos);

int		philo_notify(long *start_time, t_philo *philo, char *msg);
void	ft_usleep(long time);
int		safe_malloc(void **ptr, size_t size, char *str);

#endif
