/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:03 by nradin            #+#    #+#             */
/*   Updated: 2023/03/10 15:39:39 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define THINK 1
# define FORK 2
# define EAT 3
# define SLEEP 4

typedef struct s_philo		t_philo;
typedef struct s_philo_data	t_philo_data;

struct s_philo
{
	int				index;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	uint64_t		last_meal;
	t_philo_data	*state;
};

struct s_philo_data
{
	int				num_of_philo;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				num_of_eat;
	uint64_t		start_time;
	int				is_end;
	t_philo			*philos;
	pthread_mutex_t	*action;
};

int			check_if_nums(int argc, char **argv);
int			ft_atoi(const char *nptr);
int			init_threads(pthread_t *philo, t_philo_data *philo_state);
void		join_threads(pthread_t *philo, t_philo_data *philo_state);
uint64_t	ft_get_time(void);
void		ft_usleep(uint64_t wait_time);
int			init_philos(t_philo_data *philo_state);
void		init_args(t_philo_data *philo_state, int argc, char *argv[]);
void		make_action(t_philo_data *philo_state, int index, int action);

#endif
