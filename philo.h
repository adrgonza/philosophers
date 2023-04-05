/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:45:46 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/05 15:28:19 by adrgonza         ###   ########.fr       */
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
	int	id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_sleep;
	int				nb_times_philos_eat;
}	t_philo;

typedef struct data{
	long long
	int 			number_of_philosophers;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	t_philo			*philo;
}	t_data;

int		ft_atoi(const char *str);
void	*philo_actions(void	*arg);
void	print_status(int id, char *status, t_data *data);
long long getMilliseconds();

#endif
