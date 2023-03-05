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

void	*philo_routine(void *philo_state)
{
	int	i;

	i = 0;
	while (philo_state && i < 2)
	{
		printf("sus ");
		i++;
	}
	return (NULL);
}

void	init_args(t_philo_data *philo_state, int argc, char *argv[])
{
	memset(philo_state, 0, sizeof(t_philo_data));
	philo_state->num_of_philo = ft_atoi(argv[1]);
	philo_state->time_to_die = ft_atoi(argv[2]);
	philo_state->time_to_eat = ft_atoi(argv[3]);
	philo_state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_state->num_of_eat = ft_atoi(argv[5]);
}

int	init_threads(pthread_t *philo, t_philo_data *philo_state)
{
	int	i;

	i = 0;
	while (i < philo_state->num_of_philo)
	{
		if (pthread_create(&philo[i], NULL, philo_routine, philo_state))
			return (1);
		i++;
	}
	return (0);
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
	philo = malloc(philo_state->num_of_philo * sizeof(pthread_t));
	init_threads(philo, philo_state);
	return (0);
}

