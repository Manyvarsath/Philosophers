/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:53:42 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 18:42:40 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->share->n_phork)
	{
		pthread_mutex_init(&philo[i].last_mutex, NULL);
		pthread_mutex_init(&philo->share->r_forks[i], NULL);
		pthread_mutex_init(&philo[i].must_lock, NULL);
		pthread_mutex_init(&philo[i].dead_mutex, NULL);
	}
	pthread_mutex_init(&philo->share->print_mutex, NULL);
	return (0);
}

int	full_bellies(t_philo *philo, int *count, int i)
{
	if (philo[i].share->must_eat != -1)
	{
		pthread_mutex_lock(&philo[i].must_lock);
		if (philo[i].has_eaten >= philo[i].share->must_eat)
			*count = *count + 1;
		pthread_mutex_unlock(&philo[i].must_lock);
	}
	if (*count == philo[i].share->n_phork)
	{
		pthread_mutex_lock(&philo->share->print_mutex);
		return (0);
	}
	return (1);
}

int	not_starving(t_philo *philo)
{
	long	test;
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (++i < philo->share->n_phork)
	{
		if (!full_bellies(philo, &count, i))
			return (0);
		pthread_mutex_lock(&philo[i].last_mutex);
		test = curr_time(philo[i].share->time_start + philo[i].last_eaten);
		pthread_mutex_unlock(&philo[i].last_mutex);
		pthread_mutex_lock(&philo[i].dead_mutex);
		if ((test * 1000) >= (philo[i].share->ttd * 1000))
		{
			pthread_mutex_lock(&philo[i].share->print_mutex);
			printf("%lu %d has died", curr_time(philo[i].share->time_start),
				philo[i].id);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].dead_mutex);
		usleep(100);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_share	*share;

	if (ac < 5 || ac > 6 || my_atoi(av[1]) < 0)
	{
		printf("error number of arguments is invalid");
		return (1);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * my_atoi(av[1]));
	share = (t_share *)malloc(sizeof(t_share));
	if (!philo || !share)
	{
		printf("error initial memory allocation problem\n");
		return (1);
	}
	if (error_checks(share, philo, ac, av))
	{
		printf("error initilization problem\n");
		return (1);
	}
	init_mutex(philo);
	create_threads(philo);
	return (0);
}
