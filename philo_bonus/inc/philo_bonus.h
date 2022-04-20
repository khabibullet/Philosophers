/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anemesis <anemesis@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:08:59 by anemesis          #+#    #+#             */
/*   Updated: 2022/04/20 15:36:18 by anemesis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>

typedef struct t_input
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_each_eat;
}	t_input;

typedef struct t_table
{
	t_input			inputs;
	int				philo_name;
	pthread_t		monitor;
	pid_t			pid;
	pid_t			*cpids;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_clean;
	sem_t			*sem_fed;
	long			start_time;
	long			last_meal;
}	t_table;

int		ft_atoi(const char	*str);

int		init_inputs(int argc, char ***argv, t_input *inputs);
int		init_philos(t_table *table);
int		init_forks(t_table *table, int num_of_philos);
int		init_monitors(t_table *table);

int		start_dinner(t_table *table);
void	death_monitor(t_table *table);
void	fed_monitor(t_table *table);
int		full_clean(t_table *table);

int		ft_usleep(long time);
long	get_sys_time(void);
int		philo_notify(t_table *table, char *msg, int death);
int		pthread_safe_create(pthread_t *thread, void (*f)(t_table *table), void *table);
int		pthread_safe_detach(pthread_t thread);

#endif
