/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:26:48 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 05:53:04 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>		// printf
# include <stdlib.h> 	// malloc - free
# include <unistd.h> 	// usleep - write
# include <sys/time.h>	// gettimeofday -- unnecesary now since in time file
# include <sys/types.h>	// waitpid
# include <sys/wait.h>	// waitpid
# include <pthread.h>	// pthread functions
# include <semaphore.h>	// sem functions
# include <signal.h>	// sig functions
# include <fcntl.h>
# include <stdatomic.h> //

//Data
typedef struct s_share
{
	int				chopsticks;
	int				must_eat;
	long			ttd;
	long			tte;
	long			tts;
	atomic_long		time_start;
	sem_t			*print_sem;
	sem_t			*chopsticks_sem;
	sem_t			*starve_sem;
}	t_share;

typedef struct s_philo
{
	int				id;
	int				has_eaten;
	atomic_long		last_eaten;
	pid_t			pid;
	pthread_t		thread;
	t_share			*share;
}	t_philo;

//ERROR
int		error_checks(t_share *share, t_philo *philo, int ac, char **av);

//UTILS
int		my_atoi(const char *s);

//TIME
long	curr_time(long time_start);
void	loiter(long usec);

//OPS
void	time_to_philosophy(t_philo *philo);

#endif