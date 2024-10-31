/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:58:39 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/23 16:23:40 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_not_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (!(argc >= 5 && argc <= 6))
		return (1);
	if (is_not_digit(argv))
		return (1);
	if (ft_atoi(argv[1]) == 1)
	{
		usleep(ft_atoi(argv[3]) * 1000);
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (1);
	}
	return (0);
}
