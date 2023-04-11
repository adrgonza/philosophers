/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:27:45 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/11 23:06:10 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-protect line 33
-implement better death
-fix leaks and pthreads problems
*/

void ft_paradise(t_data *data)
{
	long long	act_time;
	int			nb_philos_eaten;
	int			i;

	nb_philos_eaten = 0;
	while (1) /* check if there is a dead philo  */
	{
		i = -1;
		while (++i < data->number_of_philosophers) /* iterate every thread */
		{
			act_time = timex() - data->philo->star_time;
			if (act_time - data->philo[i].last_time_eat > data->philo[i].time_to_die) /* check if in that thread the philosopher died */
			{
				printf("%lldms philo %d has died\n", act_time, data->philo[i].id);
				exit(0);
			}
			if ((data->philo[i].times_eaten == data->philo[i].nb_times_philos_eat) && data->philo[i].alredy_eaten == 0)
			{
				nb_philos_eaten++;
				data->philo[i].alredy_eaten = 1;
				if (nb_philos_eaten == data->number_of_philosophers)
					exit(0);
			}
		}
	}
}

void	*philo_actions(void	*arg)
{
	t_philo *philo;

	philo = arg; /* give the value of arg to philo */
	while (philo->start == 0); /* make all the philos wait for beeing all created */
	if ((philo->id % 2) == 0) /* checks if the philo is pair to give him delay */
		usleep(50);
	philo->last_time_eat = 0;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork); /* lock left fork */
		printf("%lldms philo %d has taken a fork\n", timex() - philo->star_time, philo->id); /* take left */
		pthread_mutex_lock(philo->right_fork); /* lock right fork */
		printf("%lldms philo %d has taken a fork\n", timex() - philo->star_time, philo->id); /* take right fork */
		philo->last_time_eat = timex() - philo->star_time;
		printf("%lldms philo %d is eating\n", timex() - philo->star_time, philo->id); /* print is eating */
		if (philo->times_eaten != -1)
			philo->times_eaten++;
		ft_sleep(philo->time_to_eat); /* wait the time to eat */
		pthread_mutex_unlock(philo->left_fork); /* release left fork */
		pthread_mutex_unlock(philo->right_fork); /* release right fork */
		printf("%lldms philo %d is sleeping\n", timex() - philo->star_time, philo->id); /* print is sleeping */
		ft_sleep(philo->time_sleep); /* wait time for sleep */
		printf("%lldms philo %d is thinking\n", timex() - philo->star_time, philo->id); /* print is thinking */
	}
}

void	create_pthread(t_data	*data, int argc, char **argv)
{
	int	i;

	data->start_race = 0;
	i = -1;
	data->start_time = timex();  /* get the time at program start */
	while (++i < data->number_of_philosophers) /* have to create every pthread and put in the philo structure*/
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL)) /* mutex creation */
			exit(0);
		data->philo[i].star_time = data->start_time; /* star time writted on data give it to philo */
		data->philo[i].id = i + 1; /* philo id */
		data->philo[i].right_fork = &(data->forks[i]); /* putting every fork in a fork variable */
		data->philo[i].left_fork = &(data->forks[(i + 1) % (data->number_of_philosophers)]); /* module x of x number is 0 */
		data->philo[i].time_to_die = ft_atoi(argv[2]);
		data->philo[i].time_to_eat = ft_atoi(argv[3]);
		data->philo[i].time_sleep = ft_atoi(argv[4]);
		data->philo[i].nb_times_philos_eat = -1; /* times philo has to eat inicied at -1 */
		if (argc == 6)
			data->philo[i].nb_times_philos_eat = ft_atoi(argv[5]); /* if there is value put it in the variable */
		data->philo[i].alredy_eaten = 0;
		data->philo[i].start = &data->start_race; /* gives the acces to the same variable to all philos */
		pthread_create(&(data->philosophers[i]), NULL, philo_actions, &(data->philo[i])); /* creating every pthread */
	}
	data->start_race = 1; /* al threads starts */
	ft_paradise(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	int		j;

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
	if (!data.philosophers)
		return (0);
	create_pthread(&data, argc, argv);
}
