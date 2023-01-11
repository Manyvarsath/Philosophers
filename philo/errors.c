/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:55:58 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 16:56:43 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared(t_share *share, int ac, char **av)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	share->n_phork = my_atoi(av[1]);
	share->ttd = my_atoi(av[2]);
	share->tte = my_atoi(av[3]);
	share->tts = my_atoi(av[4]);
	share->must_eat = -1;
	share->time_start = begin.tv_usec / 1000 + begin.tv_sec * 1000;
	if (ac == 6)
	{
		share->must_eat = my_atoi(av[5]);
		if (share->must_eat <= 0)
			return (-1);
	}
	if (share->n_phork < 1 || share->ttd <= 0 || share->tte <= 0
		|| share->tts <= 0)
		return (-1);
	share->r_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* share->n_phork);
	if (!share->r_forks)
		return (-1);
	return (0);
}

int	init_philos(t_share *share, t_philo *philo, int ac, char **av)
{
	int	i;

	i = -1;
	if (init_shared(share, ac, av))
	{
		printf("error init shared\n");
		return (-1);
	}
	while (++i < my_atoi(av[1]))
	{
		philo[i].last_eaten = 0;
		philo[i].has_eaten = 0;
		philo[i].id = i + 1;
		philo[i].share = share;
	}
	return (0);
}

int	error_checks(t_share *share, t_philo *philo, int ac, char **av)
{
	if (init_philos(share, philo, ac, av))
	{
		printf("error init data\n");
		free(share);
		free(philo);
		return (1);
	}
	return (0);
}
