/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:00 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 18:56:29 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long	curr_time(long time_start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_usec / 1000 + current.tv_sec * 1000) - time_start);
}

void	loiter(long wait_time)
{
	long	time_lag;

	time_lag = curr_time(0);
	while (curr_time(time_lag) * 1000 < wait_time)
		usleep(700);
}
