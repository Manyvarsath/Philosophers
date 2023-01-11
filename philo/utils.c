/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkamal <bkamal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:12:04 by bkamal            #+#    #+#             */
/*   Updated: 2023/01/08 16:56:20 by bkamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	my_iskhawi(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r'
		|| c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	my_atoi(const char *s)
{
	int				sign;
	int				i;
	unsigned long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (my_iskhawi(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			nb = (nb * 10) + (s[i] - '0');
		else
			return (0);
		i++;
	}
	return (nb * sign);
}
