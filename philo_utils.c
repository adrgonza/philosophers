/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:24:40 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/10 17:18:57 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str) /* atoi recreation */
{
	long int	nb;
	int			i;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nb = (str[i++] - '0') + nb * 10;
	if ((sign * nb) > 2147483647) /* check max int */
		exit(0);
	return (sign * nb);
}

long long timex(void)
{
	struct timeval timev;

	gettimeofday(&timev, NULL);
	return(timev.tv_sec * 1000) + (timev.tv_usec / 1000);
}
