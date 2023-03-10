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

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philo_data	*philo_state;

	philo_state = NULL;
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong amount of arguments!\n", 28);
		return (1);
	}
	if (!check_if_nums(argc, argv))
	{
		write(2, "Arguments need to have unsigned int type!\n", 34);
		return (1);
	}
	philo_state = malloc(sizeof(t_philo_data));
	init_args(philo_state, argc, argv);
	init_philos(philo_state);
	init_semaphore(philo_state);
	init_processes(philo_state);
	return (0);
}
