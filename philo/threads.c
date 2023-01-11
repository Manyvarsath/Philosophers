/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 02:56:56 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 18:40:03 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_print(t_philo *philo, char *sentence)
{
	pthread_mutex_lock(&philo->share->print_mutex);
	printf("%lu %d %s\n",
		curr_time(philo->share->time_start), philo->id, sentence);
	pthread_mutex_unlock(&philo->share->print_mutex);
}

void	gorge(t_philo *philo)
{
	pthread_mutex_lock(&philo->share->r_forks[philo->id
		% philo->share->n_phork]);
	mutex_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->share->r_forks[philo->id - 1]);
	mutex_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->dead_mutex);
	pthread_mutex_lock(&philo->last_mutex);
	mutex_print(philo, "is eating");
	philo->last_eaten = curr_time(philo->share->time_start);
	pthread_mutex_lock(&philo->must_lock);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->must_lock);
	pthread_mutex_unlock(&philo->last_mutex);
	pthread_mutex_unlock(&philo->dead_mutex);
	loiter(philo->share->tte * 1000);
	pthread_mutex_unlock(&philo->share->r_forks[philo->id
		% philo->share->n_phork]);
	pthread_mutex_unlock(&philo->share->r_forks[philo->id - 1]);
}

void	slumber(t_philo *philo)
{
	mutex_print(philo, "is sleeping");
	loiter(philo->share->tts * 1000);
}

void	*routine(void	*param)
{
	while (1)
	{
		gorge((t_philo *)param);
		slumber((t_philo *)param);
		mutex_print((t_philo *)param, "is thinking");
	}
	return (NULL);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->share->n_phork)
	{
		philo[i].last_eaten = curr_time(philo->share->time_start);
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		i += 2;
	}
	i = 1;
	usleep(15000);
	while (i < philo->share->n_phork)
	{
		philo[i].last_eaten = curr_time(philo->share->time_start);
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
			return (1);
		i += 2;
	}
	while (1)
	{
		if (!not_starving(philo))
			return (0);
	}
	return (0);
}
