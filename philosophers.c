/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:27:45 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/25 18:01:33 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	ft_exit(t_data *data)
{
	free(data->philosophers);
	exit(0);
}

int	ft_atoi(const char *str) /* atoi recreation */
{
	int	i;
	int	nb;
	int	sign;

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
	return (sign * nb);
}
int create_pthread(t_data	*data)
{
	int i;

	data->forks = malloc((sizeof(pthread_mutex_t) * data->number_of_philosophers));  /* allocate memory for mutex */
	if (!data->forks)
		return (0);
	data->philosophers = malloc(sizeof(pthread_t) * (data->number_of_philosophers)); /* allocate memory for threads */
	if(!data->philosophers)
		return(0);
	i = -1;
	while (++i < data->number_of_philosophers)	/* have to create every pthread and put in the philo structure*/
	{
		data->philo = malloc(sizeof(t_philo)); /* allocate memory for every strucuture who is gonna be sent to every thread */
    	if (!data->philo)
        	return (0);
		data->philo->phnb = i + 1; /* philo id */
		data->philo[i].left_fork = data->forks[i]; /* putting every fork in a fork variable */
		data->philo[i].right_fork = data->forks[i + 1];
		pthread_mutex_init(&data->forks[i], NULL); /* mutex creation */
		pthread_create(&data->philosophers[i], NULL, philo_actions, data); /* creating every pthread */
		usleep(100);
	}
	return (1);
}

int check_param(int argc, char **argv, t_data	*data) /* need to check max int */
{
	int i;
	int j;

	j = 0;
	while (++j < argc) /* check imput is nb */
	{
		i = -1;
		while (argv[j][++i])
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
	}
	gettimeofday(&data->start_time, NULL);  /* save every imput value in each variable */
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return(1);
}

int main (int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || !check_param(argc, argv, &data))
		return (printf("Error"));
	if (!create_pthread(&data))
		return (0);
	return (0);
}
