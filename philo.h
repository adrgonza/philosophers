/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:45:46 by adrgonza          #+#    #+#             */
/*   Updated: 2023/03/23 00:11:17 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
#include <sys/time.h>

typedef struct philo{
	int phnb;
}	t_philo;

typedef struct data{
	int			time_to_die;
	int			time_to_eat;
	int			time_sleep;
	int			number_of_times_each_philosopher_must_eat;
	int 		number_of_philosophers;
	struct timeval	start_time;
	pthread_t	*philosophers;
	t_philo		*philo;
}	t_data;

int	ft_atoi(const char *str);
int create_pthread(t_data	*data);
void	*theres_hunger(void	*arg);

#endif
