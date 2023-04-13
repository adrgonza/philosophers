/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:24:40 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/13 18:49:10 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_free(t_data *data)
{
	free(data->philo);
	free(data->philosophers);
	free(data->forks);
	free(data->defender);
	free(data->print_lock);
}
void	ft_destroy_threads(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philos_nb)
	{
		pthread_mutex_unlock(data->philo[i].defender);
		pthread_join(data->philosophers[i], NULL);
	}
	i = -1;
	while (++i < data->philos_nb)
	{
		pthread_mutex_destroy(&(data->defender[i]));
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->print_lock[i]));
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
	if ((sign * nb) > 2147483647)
		return (-1);
	return (sign * nb);
}

long long get_time(void)
{
	struct timeval timev;

	gettimeofday(&timev, NULL);
	return(timev.tv_sec * 1000) + (timev.tv_usec / 1000);
}
void ft_sleep(int time)
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

void ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	if (*(philo->stop) == 1)
		printf("%lldms philo %d %s", get_time() - philo->star_time, philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
}
