/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:54:18 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/27 02:34:47 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(int id, char *status, t_data *data)
{
	gettimeofday(&data->start_time, NULL);
	data->current_time = (data->tv_sec - data->start_time.tv_sec) * 10 + (data->tv_usec - data->start_time.tv_usec) / 1000;
	printf("%lldms philo %d %s\n", data->current_time, id, status);
}
