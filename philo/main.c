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
		if (now - philo_state->philos[i].last_meal > \
			philo_state->time_to_die)
		{
			printf("%llu %d is died\n", \
				ft_get_time() - philo_state->start_time, i);
			philo_state->is_end = 1;
			return (1);
		}
		if (philo_state->num_of_eat)
			if (philo_state->philos[i].meals == philo_state->num_of_eat)
				eated++;
		pthread_mutex_unlock(philo_state->action);
		i++;
	}
	if (philo_state->num_of_eat && eated == philo_state->num_of_philo)
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

int	main(int argc, char *argv[])
{
	pthread_t		*philo;
	t_philo_data	*philo_state;

	philo = NULL;
	philo_state = NULL;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong amount of arguments!\n", 28);
		return (1);
	}
	if (!check_if_nums(argc, argv))
	{
		write(2, "Arguments need to have int type!\n", 34);
		return (1);
	}
	philo_state = malloc(sizeof(t_philo_data));
	init_args(philo_state, argc, argv);
	init_philos(philo_state);
	philo = malloc(philo_state->num_of_philo * sizeof(pthread_t));
	init_threads(philo, philo_state);
	check_dead_philo(philo_state);
	join_threads(philo, philo_state);
	return (0);
}
