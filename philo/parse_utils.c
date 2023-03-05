/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:33:54 by nradin            #+#    #+#             */
/*   Updated: 2023/03/05 15:55:23 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_nums(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] == '\f' || argv[i][j] == '\n' || argv[i][j] == '\r'
			|| argv[i][j] == '\t' || argv[i][j] == '\v' || argv[i][j] == ' ')
			j++;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		if (!argv[i][j])
			return (0);
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		s;
	long	num;

	i = 0;
	s = 1;
	num = 0;
	while (*(nptr + i) == '\f' || *(nptr + i) == '\n' || *(nptr + i) == '\r'
		|| *(nptr + i) == '\t' || *(nptr + i) == '\v' || *(nptr + i) == ' ')
		i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
			s = -1;
		i++;
	}
	while (*(nptr + i) > 47 && *(nptr + i) < 58)
	{
		num = num * 10 + (*(nptr + i) - 48);
		i++;
	}
	return ((int)(num * s));
}
