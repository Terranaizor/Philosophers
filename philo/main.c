/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nradin <nradin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/03/05 13:57:17 by nradin			#+#	#+#			 */
/*   Updated: 2023/03/05 16:26:34 by nradin		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

int	check_end_conditions(t_philo_data *philo_state, uint64_t now)
{
	int	i;
	int	eated;

	i = 0;
	eated = 0;
	while (i < philo_state->num_of_philo)
	{
		if (now > philo_state->philos[i].last_meal + \
			philo_state->time_to_die)
		{
			printf("%llu %d is died\n", now, i);
			philo_state->is_end = 1;
			return (1);
		}
		if (philo_state->philos[i].meals == philo_state->num_of_eat)
			eated++;
		i++;
	}
	if (eated == philo_state->num_of_philo)
		return (1);
	return (0);
}

void	check_dead_philo(t_philo_data *philo_state)
{
	uint64_t	now;

	while (1)
	{
		now = ft_get_time() - philo_state->start_time;
		pthread_mutex_lock(philo_state->action);
		if (check_end_conditions(philo_state, now))
		{
			philo_state->is_end = 1;
			pthread_mutex_unlock(philo_state->action);
			break ;
		}
		pthread_mutex_unlock(philo_state->action);
	}
}

int	check_args(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong amount of arguments!\n", 28);
		return (1);
	}
	else if (!check_if_nums(argc, argv))
	{
		write(2, "Arguments need to have unsigned int type!\n", 34);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	pthread_t		*philo;
	t_philo_data	*philo_state;

	philo = NULL;
	philo_state = NULL;
	if (check_args(argc, argv))
		return (1);
	philo_state = malloc(sizeof(t_philo_data));
	if (!philo_state)
		return (free_memory(philo_state));
	memset(philo_state, 0, sizeof(t_philo_data));
	if (init_args(philo_state, argc, argv) || init_philos(philo_state))
		return (free_memory(philo_state));
	philo = malloc(philo_state->num_of_philo * sizeof(pthread_t));
	if (!philo)
		return (free_memory(philo_state));
	if (init_threads(philo, philo_state))
		return (free_memory(philo_state));
	check_dead_philo(philo_state);
	join_threads(philo, philo_state);
	free_memory(philo_state);
	return (0);
}
