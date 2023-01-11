/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 04:27:04 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 16:55:57 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_prev(void)
{
	sem_unlink("/chopsticks");
	sem_unlink("/print");
	sem_unlink("/starve");
}

int	init_shared(t_share *share, int ac, char **av)
{
	struct timeval	begin;

	gettimeofday(&begin, NULL);
	share->chopsticks = my_atoi(av[1]);
	share->ttd = my_atoi(av[2]);
	share->tte = my_atoi(av[3]);
	share->tts = my_atoi(av[4]);
	share->time_start = begin.tv_usec / 1000 + begin.tv_sec * 1000;
	if (ac == 6)
	{
		share->must_eat = my_atoi(av[5]);
		if (share->must_eat <= 0)
			return (-1);
	}
	if (share->chopsticks <= 0 || share->ttd <= 0 || share->tte <= 0
		|| share->tts <= 0)
		return (-1);
	unlink_prev();
	share->chopsticks_sem = sem_open("/chopsticks",
			O_CREAT, 0644, share->chopsticks);
	share->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	share->starve_sem = sem_open("/starve", O_CREAT, 0644, 1);
	if (!share->chopsticks_sem || !share->print_sem || !share->starve_sem)
		return (-1);
	return (0);
}

int	init_philos(t_share *share, t_philo *philo, int ac, char **av)
{
	int	i;

	i = -1;
	if (init_shared(share, ac, av))
		return (-1);
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
	share->must_eat = -1;
	if (init_philos(share, philo, ac, av))
		return (1);
	return (0);
}
