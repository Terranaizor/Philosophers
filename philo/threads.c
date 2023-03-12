/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:59 by nradin            #+#    #+#             */
/*   Updated: 2023/03/12 14:05:50 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2)
		ft_usleep(philo->state->time_to_eat);
	while (!philo->state->is_end)
	{
		pthread_mutex_lock(philo->left_fork);
		make_action(philo->state, philo->index, FORK);
		if (philo->left_fork == philo->right_fork)
			return (NULL);
		pthread_mutex_lock(philo->right_fork);
		make_action(philo->state, philo->index, FORK);
		make_action(philo->state, philo->index, EAT);
		ft_usleep(philo->state->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->state->num_of_eat && \
			philo->meals == philo->state->num_of_eat)
			break ;
		make_action(philo->state, philo->index, SLEEP);
		ft_usleep(philo->state->time_to_sleep);
		make_action(philo->state, philo->index, THINK);
	}
	return (NULL);
}

void	join_threads(pthread_t *philo, t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	free(philo);
}

int	init_threads(pthread_t *philo, t_philo_data *philo_state)
{
	int	i;

	i = 0;
	philo_state->start_time = ft_get_time();
	while (i < philo_state->num_of_philo)
	{
		if (pthread_create(&philo[i], NULL, philo_routine, \
			&philo_state->philos[i]))
		{
			free(philo);
			return (1);
		}
		i++;
	}
	return (0);
}
