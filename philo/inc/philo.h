/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:04:38 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/25 12:29:55 by anemesis         ###   ########.fr       */
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
	int				eat_count;
	long			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_t		thread;
	pthread_t		death_check;
	t_input			*inputs;
	long			*start_time;
	int				*meal_end;

}	t_philo;

typedef struct t_table
{
	t_input			inputs;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	int				meal_end;
	long			start_time;
}	t_table;

int		ft_atoi(const char	*str);

int		init_inputs(int argc, char ***argv, t_input *inputs);
int		init_philos(t_table *table, int num_of_philos);
int		init_forks(t_table *table, int num_of_philos);

int		start_dinner(t_table *table);
void	*eat_or_die(t_philo *philo);
int		end_dinner(t_table *table);
int		eat_sleep_repeat(t_philo *philo);
void	*death_monitor(void *arg);

int		ft_usleep(long time, t_philo *philo);
long	get_sys_time(void);
int		philo_notify(t_philo *philo, char *msg, int death);

#endif
