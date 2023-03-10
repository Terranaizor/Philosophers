/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:17:59 by nradin            #+#    #+#             */
/*   Updated: 2023/03/10 14:21:58 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_action(t_philo_data *philo_state, int index, int action)
{
	sem_wait(philo_state->action);
	if (philo_state->is_end)
	{
		sem_post(philo_state->action);
		return ;
	}
	if (action == THINK)
		printf("%llu %d is thinking\n", \
			ft_get_time() - philo_state->start_time, index);
	else if (action == FORK)
		printf("%llu %d has taken a fork\n", \
			ft_get_time() - philo_state->start_time, index);
	else if (action == EAT)
	{
		sem_wait(philo_state->eat_check);
		printf("%llu %d is eating\n", \
			ft_get_time() - philo_state->start_time, index);
		philo_state->philos[index].last_meal = \
			ft_get_time() - philo_state->start_time;
		philo_state->philos[index].meals += 1;
		philo_state->philos[index].last_meal = \
			ft_get_time() - philo_state->start_time;
		sem_post(philo_state->eat_check);
	}
	else if (action == SLEEP)
		printf("%llu %d is sleeping\n", \
			ft_get_time() - philo_state->start_time, index);
	sem_post(philo_state->action);
}

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
			printf("%llu %d is died\n", \
				ft_get_time() - philo->state->start_time, philo->index);
			philo->state->is_end = 1;
			sem_wait(philo->state->action);
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
