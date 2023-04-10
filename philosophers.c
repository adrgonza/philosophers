/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:27:45 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/10 17:27:25 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-implement mutex who protects printf
-implement times eaten
-implement better death
-fix leaks and pthreads problems

*/

int print_philos(t_philo *philo, char *str)
{
	long long act_time;
	//lock mutex
	act_time = timex() - philo->star_time;
	if (act_time - philo->last_time_eat > philo->time_to_die)
	{
		printf("%lldms philo %d has died\n", act_time, philo->id);
		exit(0);
	}
	//si algiuno
	printf("%lldms philo %d %s", act_time, philo->id, str);
	//unlock the mutex
	return (0);
}

void	*philo_actions(void	*arg)
{
	t_philo *philo;

	philo = arg;
	while (!philo->bang);
	if ((philo->id % 2) == 0)
		usleep(50);
	philo->last_time_eat = timex() - philo->star_time;
	while(1)
	{
		pthread_mutex_lock(philo->left_fork); /* lock left fork */
		print_philos(philo, "has taken a fork\n"); /* take left fork */
		pthread_mutex_lock(philo->right_fork); /* lock right fork */
		print_philos(philo, "has taken a fork\n"); /* take right fork */
		philo->last_time_eat = timex() - philo->star_time;
		print_philos(philo, "is eating\n"); /* print is eating */
		usleep(philo->time_to_eat * 1000); /* wait the time to eat */
		pthread_mutex_unlock(philo->left_fork); /* release left fork */
		pthread_mutex_unlock(philo->right_fork); /* release right fork */
		print_philos(philo, "is sleeping\n"); /* print is sleeping */
		usleep(philo->time_sleep * 1000); /* wait time for sleep */
		print_philos(philo, "is thinking\n"); /* print is thinking */
	}
	return (NULL);
}

int create_pthread(t_data	*data, int argc, char **argv)
{
	int bang; /* makes start al threads at the same time */
	int i;

    data->start_time = timex();  /* get the time at program start */
	bang = 0;
	i = -1;
	while (++i < data->number_of_philosophers)	/* have to create every pthread and put in the philo structure*/
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL)) /* mutex creation */
			return (0);
		data->philo[i].nb_times_philos_eat = -1; /* times philo has to eat inicied at -1 */
		if (argc == 6)
			data->philo[i].nb_times_philos_eat = ft_atoi(argv[5]); /* if there is value put it in the variable */
		data->philo[i].star_time = data->start_time; /* star time writted on data give it to philo */
		data->philo[i].id = i + 1; /* philo id */
		data->philo[i].right_fork = &(data->forks[i]); /* putting every fork in a fork variable */
		data->philo[i].left_fork = &(data->forks[(i + 1) % (data->number_of_philosophers)]); /* module x of x number is 0 */
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_sleep = ft_atoi(argv[4]);
		data->philo[i].bang = &bang; /* gives the acces to the same variable to all philos */
		pthread_create(&(data->philosophers[i]), NULL, philo_actions, &(data->philo[i])); /* creating every pthread */
	}
	bang = 1; /* al threads starts */
	while (1);
}

int main (int argc, char **argv)
{
	t_data	data;
	int i;
	int j;

	if (argc < 5 || argc > 6) /* check there is only five or six arguments */
		return (0);
	j = 0;
	while (++j < argc) /* check imput is nb */
	{
		i = -1;
		while (argv[j][++i])
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
	}
	data.number_of_philosophers = ft_atoi(argv[1]); /* get how many philos are */
	data.philo = malloc(sizeof(t_philo) * data.number_of_philosophers); /* allocate memory for every strucuture who is gonna be sent to every thread */
	if (!data.philo)
		return (0);
	data.forks = malloc(sizeof(pthread_mutex_t) * data.number_of_philosophers);  /* allocate memory for mutex */
	if (!data.forks)
		return (0);
	data.philosophers = malloc(sizeof(pthread_t) * (data.number_of_philosophers)); /* allocate memory for threads */
	if(!data.philosophers || !create_pthread(&data, argc, argv))
		return(0);
}
