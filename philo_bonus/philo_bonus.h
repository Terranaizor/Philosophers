/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:03 by nradin            #+#    #+#             */
/*   Updated: 2023/03/12 14:21:46 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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
	int				pid;
	uint64_t		last_meal;
	pthread_t		death_check;
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
	sem_t			*eat_check;
	sem_t			*forks;
	sem_t			*action;
	t_philo			*philos;
};

int			check_if_nums(int argc, char **argv);
int			ft_atoi(const char *nptr);
int			init_processes(t_philo_data *philo_state);
int			init_semaphore(t_philo_data *philo_state);
uint64_t	ft_get_time(void);
void		ft_usleep(uint64_t wait_time);
int			init_philos(t_philo_data *philo_state);
int			init_args(t_philo_data *philo_state, int argc, char *argv[]);
int			free_memory(t_philo_data *philo_state);
void		make_action(t_philo_data *philo_state, int index, int action);

#endif
