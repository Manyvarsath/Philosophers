/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:33:51 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 05:52:30 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> 	// printf
# include <stdlib.h> 	// malloc - free
# include <unistd.h> 	// usleep - write
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// pthread functions

//Data
typedef struct s_share
{
	int				n_phork;
	int				must_eat;
	long			ttd;
	long			tte;
	long			tts;
	long			time_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*r_forks;
}	t_share;

typedef struct s_philo
{
	int				has_eaten;
	int				id;
	long			last_eaten;
	pthread_mutex_t	last_mutex;
	pthread_mutex_t	must_lock;
	pthread_mutex_t	dead_mutex;
	pthread_t		thread;
	t_share			*share;
}	t_philo;

//ERROR
int		error_checks(t_share *share, t_philo *philo, int ac, char **av);

//THREADS
int		create_threads(t_philo *philo);
int		not_starving(t_philo *philo);

//UTILS
int		my_atoi(const char *s);

//TIME
long	curr_time(long time_start);
void	loiter(long usec);

#endif
