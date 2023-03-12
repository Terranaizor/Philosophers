/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:25 by nradin            #+#    #+#             */
/*   Updated: 2023/03/12 14:05:18 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		if (philo_state->philos[i].right_fork)
		{
			pthread_mutex_destroy(philo_state->philos[i].right_fork);
			free(philo_state->philos[i].right_fork);
		}
		i++;
	}
	free(philo_state->philos);
}

int	free_memory(t_philo_data *philo_state)
{
	if (philo_state)
	{
		if (philo_state->action)
		{
			pthread_mutex_destroy(philo_state->action);
			free(philo_state->action);
		}
		if (philo_state->philos)
			free_philos(philo_state);
		free(philo_state);
	}
	return (1);
}

int	init_args(t_philo_data *philo_state, int argc, char *argv[])
{
	philo_state->num_of_philo = ft_atoi(argv[1]);
	philo_state->philos = malloc(sizeof(t_philo) * philo_state->num_of_philo);
	if (!philo_state->philos)
		return (free_memory(philo_state));
	memset(philo_state->philos, 0, sizeof(t_philo) * philo_state->num_of_philo);
	philo_state->time_to_die = ft_atoi(argv[2]);
	philo_state->time_to_eat = ft_atoi(argv[3]);
	philo_state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_state->num_of_eat = ft_atoi(argv[5]);
	else
		philo_state->num_of_eat = -1;
	philo_state->is_end = 0;
	philo_state->action = malloc(sizeof(pthread_mutex_t));
	if (!philo_state->action)
		return (free_memory(philo_state));
	if (pthread_mutex_init(philo_state->action, NULL) == -1)
		return (free_memory(philo_state));
	return (0);
}

int	init_philos(t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		philo_state->philos[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo_state->philos[i].right_fork)
			return (free_memory(philo_state));
		philo_state->philos[i].state = philo_state;
		philo_state->philos[i].index = i;
		if (pthread_mutex_init(philo_state->philos[i].right_fork, NULL))
			return (free_memory(philo_state));
		if (i > 0)
			philo_state->philos[i].left_fork = \
				philo_state->philos[i - 1].right_fork;
		philo_state->philos[i].meals = 0;
		i++;
	}
	philo_state->philos[0].left_fork = philo_state->philos[i - 1].right_fork;
	return (0);
}
