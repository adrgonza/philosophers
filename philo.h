/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:15:01 by adrgonza          #+#    #+#             */
/*   Updated: 2023/04/12 23:32:04 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct philo{
	int				*start;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_sleep;
	int				nb_philos_eat;
	int				alredy_eaten;
	int				times_eaten;
	long long		star_time;
	long long		last_time_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*defender;
}	t_philo;

typedef struct data
{
	int				philos_nb;
	int				nb_philos_eaten;
	int				start_race;
	long long		start_time;
	long long		act_time;
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*defender;
	t_philo			*philo;
} t_data;

int	ft_atoi_s(const char *str);
long long get_time(void);
void ft_sleep(int time);
void ft_free(t_data *data, int nb);
void	ft_destroy_threads(t_data *data);

#endif
