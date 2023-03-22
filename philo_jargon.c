/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_jargon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:22:49 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/23 00:34:23 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*not_thinking(t_data *data)
{
	printf("xms philo %d is thinking\n", data->philo->phnb);
	theres_hunger(data);
	return (NULL);
}

void	*guys_are_tired(t_data *data)
{
	printf("xms philo %d is sleeping\n", data->philo->phnb);
	not_thinking(data);
	return (NULL);
}

void	*lunch_time(t_data *data)
{
	printf("xms philo %d is eating\n", data->philo->phnb);
	guys_are_tired(data);
	return(NULL);
}

void	*theres_hunger(void	*arg)
{
	t_data *data;

	data = arg;
	printf("xms philo %d has taken a fork\n", data->philo->phnb);
	lunch_time(data);
	return (NULL);
}

