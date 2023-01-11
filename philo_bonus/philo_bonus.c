/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:26:52 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 18:22:45 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	all_done(t_philo *philo)
{
	int	i;
	int	stat;

	i = -1;
	while (++i < philo->share->chopsticks)
	{
		waitpid(-1, &stat, 0);
		if (!stat)
		{
			i = -1;
			while (++i < philo->share->chopsticks)
				kill(philo[i].pid, SIGKILL);
			break ;
		}
	}
	sem_close(philo->share->chopsticks_sem);
	sem_close(philo->share->print_sem);
	sem_close(philo->share->starve_sem);
	sem_unlink("/chopsticks");
	sem_unlink("/print");
	sem_unlink("/starve");
	free(philo->share);
	free(philo);
}

int	all_ops(t_philo *philo)
{
	int	i;

	i = -1;
	philo->share->time_start = curr_time(0);
	while (++i < philo->share->chopsticks)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{	
			printf("Forking error");
			return (1);
		}
		if (philo[i].pid == 0)
			time_to_philosophy(&philo[i]);
		usleep(100);
	}
	all_done(philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_share	*share;

	if (ac < 5 || ac > 6 || my_atoi(av[1]) < 0)
	{
		printf("Not enough arguments\n");
		return (1);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * my_atoi(av[1]));
	share = (t_share *)malloc(sizeof(t_share));
	if (!philo || !share)
	{
		printf("Memory allocation problem\n");
		return (1);
	}
	if (error_checks(share, philo, ac, av))
	{
		printf("Initialization error\n");
		free(share);
		free(philo);
		return (1);
	}
	return (all_ops(philo));
}
