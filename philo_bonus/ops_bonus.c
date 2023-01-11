/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 05:31:27 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 20:05:16 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*starvation(void *param)
{
	atomic_long	test;

	while (1)
	{
		test = curr_time(((t_philo *)param)->share->time_start
				+ ((t_philo *)param)->last_eaten);
		sem_wait(((t_philo *)param)->share->starve_sem);
		if (test >= ((t_philo *)param)->share->ttd)
		{
			sem_wait(((t_philo *)param)->share->print_sem);
			printf("%lu %d has died\n",
				curr_time(((t_philo *)param)->share->time_start),
				((t_philo *)param)->id);
			exit(0);
		}
		sem_post(((t_philo *)param)->share->starve_sem);
		usleep(1000);
	}
	return (NULL);
}

void	sem_print(t_philo *philo, char *sentence)
{
	sem_wait(philo->share->print_sem);
	printf("%lu %d %s\n",
		curr_time(philo->share->time_start), philo->id, sentence);
	sem_post(philo->share->print_sem);
}

void	gorge(t_philo *philo)
{
	sem_wait(philo->share->chopsticks_sem);
	sem_print(philo, "has taken a fork");
	sem_wait(philo->share->chopsticks_sem);
	sem_print(philo, "has taken a fork");
	sem_wait(philo->share->starve_sem);
	sem_print(philo, "is eating");
	philo->last_eaten = curr_time(philo->share->time_start);
	philo->has_eaten++;
	sem_post(philo->share->starve_sem);
	loiter(philo->share->tte * 1000);
	sem_post(philo->share->chopsticks_sem);
	sem_post(philo->share->chopsticks_sem);
}

void	time_to_philosophy(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, &starvation, philo))
	{
		printf("Failure to create thread\n");
		exit(1);
	}
	philo->last_eaten = curr_time(philo->share->time_start);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (1)
	{
		gorge(philo);
		if (philo->share->must_eat != -1
			&& (philo->has_eaten > philo->share->must_eat + 1))
		{
			usleep(1000);
			exit (0);
		}
		sem_print(philo, "is sleeping");
		loiter(philo->share->tts * 1000);
		sem_print(philo, "is thinking");
	}
}
