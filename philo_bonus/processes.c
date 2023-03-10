/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:59 by nradin            #+#    #+#             */
/*   Updated: 2023/03/10 15:35:07 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void	*arg)
{
	uint64_t	now;
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		now = ft_get_time() - philo->state->start_time;
		sem_wait(philo->state->eat_check);
		if (now > philo->last_meal + philo->state->time_to_die)
		{
			sem_wait(philo->state->action);
			printf("%llu %d is died\n", \
				ft_get_time() - philo->state->start_time, philo->index);
			philo->state->is_end = 1;
			exit(1);
		}
		sem_post(philo->state->eat_check);
		if (philo->meals == philo->state->num_of_eat)
			break ;
	}
	return (NULL);
}

void	philo_eats(t_philo *philo)
{
	sem_wait(philo->state->forks);
	make_action(philo->state, philo->index, FORK);
	sem_wait(philo->state->forks);
	make_action(philo->state, philo->index, FORK);
	make_action(philo->state, philo->index, EAT);
	ft_usleep(philo->state->time_to_eat);
	sem_post(philo->state->forks);
	sem_post(philo->state->forks);
}

void	philo_routine(t_philo *philo)
{
	if (philo->index % 2)
		ft_usleep(philo->state->time_to_eat);
	pthread_create(&(philo->death_check), NULL, check_dead, philo);
	while (!philo->state->is_end)
	{
		philo_eats(philo);
		if (philo->meals == philo->state->num_of_eat)
			break ;
		make_action(philo->state, philo->index, SLEEP);
		ft_usleep(philo->state->time_to_sleep);
		make_action(philo->state, philo->index, THINK);
	}
	pthread_join(philo->death_check, NULL);
	if (philo->state->is_end == 1)
		exit(1);
	exit(0);
}

void	exit_processes(t_philo_data *philo_state)
{
	int	i;
	int	ret;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = 0;
			while (i < philo_state->num_of_philo)
			{
				kill(philo_state->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(philo_state->forks);
	sem_close(philo_state->action);
	sem_close(philo_state->eat_check);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
}

int	init_processes(t_philo_data *philo_state)
{
	int	i;

	i = 0;
	philo_state->start_time = ft_get_time();
	while (i < philo_state->num_of_philo)
	{
		philo_state->philos[i].pid = fork();
		if (philo_state->philos[i].pid < 0)
			return (1);
		if (philo_state->philos[i].pid == 0)
			philo_routine(&philo_state->philos[i]);
		i++;
	}
	exit_processes(philo_state);
	return (0);
}
