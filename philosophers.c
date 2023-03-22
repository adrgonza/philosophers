/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:27:45 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/23 00:17:18 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_pthread(t_data	*data)
{
	int i;

	data->philosophers = malloc(sizeof(pthread_t) * (data->number_of_philosophers + 1)); //aray de philos
	if(!data->philosophers)
		return(0);
	i = -1;
	while (++i < data->number_of_philosophers)	// have to create every pthread and put in the philo structure
	{
		data->philo = malloc(sizeof(t_philo)); //reservo para cada estructura de cada filo
    	if (!data->philo)
        	return (0);
		data->philo->phnb = i + 1; // id de cada filo
		pthread_create(&data->philosophers[i], NULL, theres_hunger, data); // creacionde cada hilo
		usleep(70);
	}
	return (1);
}

int check_param(int argc, char **argv, t_data	*data) // need to check max int
{
	int i;
	int j;

	j = 0;
	while (++j < argc) //check imput is nb
	{
		i = -1;
		while (argv[j][++i])
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
	}
	gettimeofday(&data->start_time, NULL);  //save every value in each variable
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (!create_pthread(data))
		return (0);
	return(1);
}

int main (int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6 || !check_param(argc, argv, &data))
		return (printf("Error"));
}
