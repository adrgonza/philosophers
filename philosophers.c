/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:27:45 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/05 15:30:35 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_died()
{

}

void	*philo_actions(void	*arg)
{
	t_philo *philo;
	long long currentTime;

	philo = arg;
	while(1)
	{
		pthread_mutex_lock(philo->left_fork); /* lock left fork */
		currentTime = getMilliseconds();
		printf("%lldms philo %d has taken a fork\n", currentTime, philo->id); /* take left fork */
		pthread_mutex_lock(philo->right_fork); /* lock right fork */
		printf("xms philo %d has taken a fork\n", philo->id); /* take right fork */
		printf("xms philo %d is eating\n", philo->id); /* print is eating */
		usleep(philo->time_to_eat * 1000); /* wait the time to eat */
		pthread_mutex_unlock(philo->left_fork); /* release left fork */
		pthread_mutex_unlock(philo->right_fork);	/* release right fork */
		printf("xms philo %d is sleeping\n", philo->id); /* print is sleeping */
		usleep(philo->time_sleep * 1000); /* wait time for sleep */
		printf("xms philo %d is thinking\n", philo->id); /* print is thinking */
	}
	return (NULL);
}

int create_pthread(t_data	*data, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < data->number_of_philosophers)	/* have to create every pthread and put in the philo structure*/
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL)) /* mutex creation */
			return (0);
		data->philo[i].nb_times_philos_eat = -1; /*  */
		if (argc == 6)
			data->philo[i].nb_times_philos_eat = ft_atoi(argv[5]);
		data->philo[i].id = i + 1; /* philo id */
		data->philo[i].right_fork = &(data->forks[i]); /* putting every fork in a fork variable */
		data->philo[i].left_fork = &(data->forks[(i + 1) % (data->number_of_philosophers)]); /* module x of x number is 0 */
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_sleep = ft_atoi(argv[4]);
		pthread_create(&(data->philosophers[i]), NULL, philo_actions, &(data->philo[i])); /* creating every pthread */
		usleep(50);
	}
	while(1);
}

int alloc_mem(int argc, char **argv, t_data	*data)
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
	data->number_of_philosophers = ft_atoi(argv[1]); /* get how many philos are */
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers); /* allocate memory for every strucuture who is gonna be sent to every thread */
	if (!data->philo)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);  /* allocate memory for mutex */
	if (!data->forks)
		return (0);
	data->philosophers = malloc(sizeof(pthread_t) * (data->number_of_philosophers)); /* allocate memory for threads */
	if(!data->philosophers)
		return(0);
	return(1);
}

int main (int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || !alloc_mem(argc, argv, &data))
		return (printf("Error"));
	create_pthread(&data, argc, argv);
	exit(0);
}
