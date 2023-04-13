/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:15:05 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/13 19:42:20 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *p, char *str)
{
	pthread_mutex_lock(p->print_lock);
	if (*(p->stop) == 1)
		printf("%lldms philo %d %s", get_time() - p->star_time, p->id, str);
	pthread_mutex_unlock(p->print_lock);
}

int	ft_check_death(t_data *data, int i)
{
	data->act_time = get_time() - data->philo->star_time;
	if (data->act_time - data->philo[i].last_time_eat
		> data->philo[i].time_to_die)
	{
		printf("%lldms philo %d has died\n", data->act_time, data->philo[i].id);
		pthread_mutex_lock(data->print_lock);
		data->stop = 0;
		pthread_mutex_unlock(data->print_lock);
		pthread_mutex_unlock(data->philo[i].left_fork);
		return (0);
	}
	if ((data->philo[i].times_eaten == data->philo[i].nb_philos_eat)
		&& data->philo[i].alredy_eaten == 0)
	{
		data->philo[i].alredy_eaten = 1;
		if (++data->nb_philos_eaten == data->philos_nb)
		{
			pthread_mutex_lock(data->print_lock);
			data->stop = 0;
			pthread_mutex_unlock(data->print_lock);
			return (0);
		}
	}
	return (1);
}

void	ft_paradise(t_data *data)
{
	int	i;

	data->nb_philos_eaten = 0;
	while (1)
	{
		i = -1;
		while (++i < data->philos_nb)
		{
			pthread_mutex_lock(data->philo[i].defender);
			if (!ft_check_death(data, i))
				return ;
			pthread_mutex_unlock(data->philo[i].defender);
		}
	}
}

void	ft_philo_actions(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->defender);
	philo->last_time_eat = get_time() - philo->star_time;
	ft_print(philo, "is eating\n");
	if (philo->nb_philos_eat != -1)
		philo->times_eaten++;
	pthread_mutex_unlock(philo->defender);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print(philo, "is sleeping\n");
	ft_sleep(philo->time_sleep);
	ft_print(philo, "is thinking\n");
}

void	*routine(void	*arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_unlock(philo->print_lock);
	if ((philo->id % 2) == 0)
		usleep(200);
	pthread_mutex_lock(philo->print_lock);
	while (*(philo->stop) == 1)
	{
		pthread_mutex_unlock(philo->print_lock);
		ft_philo_actions(philo);
		pthread_mutex_lock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->print_lock);
	return (NULL);
}
