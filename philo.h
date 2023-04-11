/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:45:46 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/11 02:03:00 by adrgonza         ###   ########.fr       */
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
# include <sys/time.h>

typedef struct philo{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int 			*start;
	int				time_to_die;
	int				time_to_eat;
	int				time_sleep;
	int				nb_times_philos_eat;
	int				times_eaten;
	int				alredy_eaten;
	long long		last_time_eat;
	long long		star_time;
}	t_philo;

typedef struct data{
	int 			number_of_philosophers;
	int				start_race;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_t		*philosophers;
	t_philo			*philo;
}	t_data;

int		ft_atoi(const char *str);
long long timex(void);

#endif
