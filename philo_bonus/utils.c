/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:16:02 by nradin            #+#    #+#             */
/*   Updated: 2023/03/10 14:59:09 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

uint64_t	ft_get_time(void)
{
	uint64_t		milliseconds;
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_usleep(uint64_t wait_time)
{
	uint64_t	time;

	time = ft_get_time();
	while (ft_get_time() - time < wait_time)
		usleep(100);
}

void	output_action(t_philo_data *philo_state, int index, char *action)
{
	sem_wait(philo_state->action);
	printf("%llu %d %s\n", \
			ft_get_time() - philo_state->start_time, index, action);
	sem_post(philo_state->action);
}

void	make_action(t_philo_data *philo_state, int index, int action)
{
	if (philo_state->is_end)
		return ;
	if (action == THINK)
		output_action(philo_state, index, "is thinking");
	else if (action == FORK)
		output_action(philo_state, index, "has taken a fork");
	else if (action == EAT)
	{
		sem_wait(philo_state->eat_check);
		output_action(philo_state, index, "is eating");
		philo_state->philos[index].last_meal = \
			ft_get_time() - philo_state->start_time;
		philo_state->philos[index].meals += 1;
		philo_state->philos[index].last_meal = \
			ft_get_time() - philo_state->start_time;
		sem_post(philo_state->eat_check);
	}
	else if (action == SLEEP)
		output_action(philo_state, index, "is sleeping");
}
