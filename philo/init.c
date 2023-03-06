/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:25 by nradin            #+#    #+#             */
/*   Updated: 2023/03/06 17:18:18 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		philo_state->num_of_eat = 0;
	philo_state->is_end = 0;
	philo_state->action = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo_state->action, NULL);
}

int	init_philos(t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		philo_state->philos[i].right_fork = malloc(sizeof(pthread_mutex_t));
		philo_state->philos[i].state = philo_state;
		philo_state->philos[i].index = i;
		pthread_mutex_init(philo_state->philos[i].right_fork, NULL);
		if (i > 0)
			philo_state->philos[i].left_fork = \
				philo_state->philos[i - 1].right_fork;
		i++;
		philo_state->philos[i].meals = 0;
	}
	philo_state->philos[0].left_fork = philo_state->philos[i - 1].right_fork;
	return (0);
}
