/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:13:19 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/12 23:45:13 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_paradise(t_data *data)
{
	int	i;

	data->nb_philos_eaten = 0;
	while (1) /* Check if there is a dead philo. */
	{
		i = -1;
		while (++i < data->philos_nb) /* Iterate every thread. */
		{
			pthread_mutex_lock(data->philo[i].defender); /* Lock a mutex to avoid a data raise. */
			data->act_time = get_time() - data->philo->star_time;
			if (data->act_time - data->philo[i].last_time_eat > data->philo[i].time_to_die) /* Checks if the philo is dead. */
			{
				printf("%lldms philo %d has died\n", data->act_time, data->philo[i].id);
				return (ft_destroy_threads(data));
			}
			if ((data->philo[i].times_eaten == data->philo[i].nb_philos_eat) && data->philo[i].alredy_eaten == 0) /* Cheks how many times a philo eat. */
			{
				data->philo[i].alredy_eaten = 1;
				if (++data->nb_philos_eaten == data->philos_nb)
					return (ft_destroy_threads(data));
			}
			pthread_mutex_unlock(data->philo[i].defender);
		}
	}
}

void	*ft_philo_actions(void	*arg)
{
	t_philo *philo;

	philo = arg;
	while (philo->start == 0); /* Makes all the philos wait for beeing all created. */
	if ((philo->id % 2) == 0) /* Checks if the philo is pair to give him delay. */
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork); /* Lock left fork. */
		printf("%lldms philo %d has taken a fork\n", get_time() - philo->star_time, philo->id);
		pthread_mutex_lock(philo->right_fork); /* Lock right fork. */
		printf("%lldms philo %d has taken a fork\n", get_time() - philo->star_time, philo->id);
		pthread_mutex_lock(philo->defender); /* Lock a mutex to avoid data raise from ft_paradise. */
		philo->last_time_eat = get_time() - philo->star_time; /* Get the last time each philo eats. */
		printf("%lldms philo %d is eating\n", get_time() - philo->star_time, philo->id);
		if (philo->nb_philos_eat != -1)
			philo->times_eaten++;
		pthread_mutex_unlock(philo->defender);
		ft_sleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork); /* Release left fork. */
		pthread_mutex_unlock(philo->right_fork); /* Release right fork. */
		printf("%lldms philo %d is sleeping\n", get_time() - philo->star_time, philo->id);
		ft_sleep(philo->time_sleep);
		printf("%lldms philo %d is thinking\n", get_time() - philo->star_time, philo->id);
	}
}
int	ft_get_values(t_data *data, int ac, char **av, int i) /* Get all values for philo structure. */
{
	if (pthread_mutex_init(&(data->forks[i]), NULL))
		return (0);
	if (pthread_mutex_init(&(data->defender[i]), NULL))
		return (0);
	data->philo[i].time_to_die = ft_atoi_s(av[2]);
	data->philo[i].time_to_eat = ft_atoi_s(av[3]);
	data->philo[i].time_sleep = ft_atoi_s(av[4]);
	data->philo[i].start = &data->start_race;
	data->philo[i].star_time = data->start_time;
	data->philo[i].id = i + 1;
	data->philo[i].right_fork = &(data->forks[i]);
	data->philo[i].left_fork = &(data->forks[(i + 1) % (data->philos_nb)]);
	data->philo[i].defender = &(data->defender[i]);
	data->philo[i].alredy_eaten = 0;
	data->philo[i].times_eaten = 0;
	data->philo[i].nb_philos_eat = -1;
	if (ac == 6)
		data->philo[i].nb_philos_eat = ft_atoi_s(av[5]);
	pthread_create(&(data->philosophers[i]), NULL, ft_philo_actions, &(data->philo[i])); /* Create threads. */
	return(1);
}

void	ft_init_data(t_data *data, int ac, char **av)
{
	int i;

	data->philos_nb = ft_atoi_s(av[1]);
	data->philo = malloc(sizeof(t_philo) * (data->philos_nb));
	if (!data->philo)
		return ;
	data->philosophers = malloc(sizeof(pthread_t) * (data->philos_nb));
	if (!data->philosophers)
		return(ft_free(data, 2));
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->philos_nb));
	if (!data->forks)
		return(ft_free(data, 3));
	data->defender = malloc(sizeof(pthread_mutex_t) * (data->philos_nb)); /* A mutex to avoid data raise in ft_paradise. */
	if (!data->defender)
		return (ft_free(data, 4));
	data->start_race = 0;
	data->start_time = get_time();
	i = -1;
	while (++i < data->philos_nb)
		if (!ft_get_values(data, ac, av, i)) /* Threads creation. */
			return (ft_free(data, 5));
	data->start_race = 1; /* All threads start doing them things at the same time. */
	ft_paradise(data); /* Checks in infinite loop if a philo died */
	return (ft_free(data, 5));
}

void leaks()
{
	system("leaks -q philo");
}
int	main(int ac, char **av)
{
	t_data	data;
	int	i;
	int	j;

	atexit(leaks);
	if (ac < 5 || ac > 6)  /* Checks there are either five or six arguments. */
		return (printf("Error\n"));
	j = 0;
	while (++j < ac) /* Checks if all the arguments passed are numerical. */
	{
		i = -1;
		while (av[j][++i])
			if (av[j][i] < '0' || av[j][i] > '9')
				return (printf("Error\n"));
	}
	if (!ft_atoi_s(av[2]) || !ft_atoi_s(av[3]) || !ft_atoi_s(av[4]))
		return (printf("Error\n"));
	if (ac == 6)
		if(!ft_atoi_s(av[5]))
			return (printf("Error\n"));
	ft_init_data(&data, ac, av);
	return (0);
}
