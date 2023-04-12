/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:24:40 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/13 01:25:31 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_free(t_data *data, int nb)
{
	if (nb >= 2)
		free(data->philo);
	if (nb >= 3)
		free(data->philosophers);
	if (nb >= 4)
		free(data->forks);
	if (nb >= 5)
		free(data->defender);
}
void	ft_destroy_threads(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philos_nb)
	{
		//pthread_join(data->philosophers[i], NULL);
		pthread_mutex_unlock(&(data->defender[i]));
		pthread_mutex_destroy(&(data->defender[i]));
		pthread_mutex_unlock(&(data->forks[i]));
		pthread_mutex_destroy(&(data->forks[i]));
	}
}
int	ft_atoi_s(const char *str)
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
	if ((sign * nb) > 2147483647) /* Check max int. */
		return (-1);
	return (sign * nb);
}

long long get_time(void)
{
	struct timeval timev;

	gettimeofday(&timev, NULL);
	return(timev.tv_sec * 1000) + (timev.tv_usec / 1000);
}
void ft_sleep(int time) /* Safe usleep recreation. */
{
	long long star_time;
	long long act_time;

	star_time = get_time();
	act_time = star_time;
	while (star_time >= (act_time - time))
	{
		act_time = get_time();
		usleep(100);
	}
}
