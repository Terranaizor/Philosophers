/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:25 by nradin            #+#    #+#             */
/*   Updated: 2023/03/10 14:07:27 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphore(t_philo_data *philo_state)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_eat");
	sem_unlink("/philo_action");
	philo_state->forks = sem_open("/philo_forks", \
		O_CREAT, S_IRWXU, philo_state->num_of_philo);
	philo_state->eat_check = sem_open("/philo_eat", \
		O_CREAT, S_IRWXU, 1);
	philo_state->action = sem_open("/philo_action", \
		O_CREAT, S_IRWXU, 1);
}

void	init_args(t_philo_data *philo_state, int argc, char *argv[])
{
	philo_state->num_of_philo = ft_atoi(argv[1]);
	philo_state->philos = malloc(sizeof(t_philo) * philo_state->num_of_philo);
	philo_state->time_to_die = ft_atoi(argv[2]);
	philo_state->time_to_eat = ft_atoi(argv[3]);
	philo_state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_state->num_of_eat = ft_atoi(argv[5]);
	else
		philo_state->num_of_eat = -1;
	philo_state->is_end = 0;
	init_semaphore(philo_state);
}

int	init_philos(t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		philo_state->philos[i].state = philo_state;
		philo_state->philos[i].index = i;
		philo_state->philos[i].meals = 0;
		i++;
	}
	return (0);
}
