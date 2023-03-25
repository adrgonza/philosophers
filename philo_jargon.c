/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_jargon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:22:49 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/25 16:58:12 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_actions(void	*arg)
{
	t_data *data;

	data = arg;
	while(1)
	{
		pthread_mutex_lock(&data->philo->left_fork); /* lock left fork */
		printf("xms philo %d has taken a fork\n", data->philo->phnb); /* take left fork */
		pthread_mutex_lock(&data->philo->right_fork); /* lock right fork */
		printf("xms philo %d has taken a fork\n", data->philo->phnb); /* take right fork */
		printf("xms philo %d is eating\n", data->philo->phnb); /* print id eating */
		usleep(data->time_to_eat * 1000); /* wait the time to eat */
		pthread_mutex_unlock(&data->philo->left_fork); /* release left fork */
		pthread_mutex_unlock(&data->philo->right_fork);	/* release right fork */
		printf("xms philo %d is sleeping\n", data->philo->phnb); /* print is sleeping */
		usleep(data->time_sleep * 1000); /* wait time for sleep */
		printf("xms philo %d is thinking\n", data->philo->phnb); /* print is thinking */
	}
	return (NULL);
}
