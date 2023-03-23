/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_jargon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:22:49 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/23 15:52:55 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*not_thinking(t_data *data)
{
	printf("xms philo %d is thinking\n", data->philo->phnb);
	return (theres_hunger(data));
}

void	*guys_are_tired(t_data *data)
{
	printf("xms philo %d is sleeping\n", data->philo->phnb);
	return (not_thinking(data));
}

void	*lunch_time(t_data *data)
{
	printf("xms philo %d is eating\n", data->philo->phnb);
	return (guys_are_tired(data));
}

void	*theres_hunger(void	*arg)
{
	t_data *data;

	data = arg;
	while(1)
	{
		printf("xms philo %d has taken a fork\n", data->philo->phnb);
		return (lunch_time(data));
	}
}
