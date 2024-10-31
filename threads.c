/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:22:02 by dpoltura          #+#    #+#             */
/*   Updated: 2024/05/24 12:51:37 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *params)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = params;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (check_value_death(philo) == 1 || check_value_meal(philo) == 1)
			break ;
		if (is_eating(philo) == 2)
			break ;
		if (check_value_death(philo))
			break ;
		if (is_sleeping(philo) == 2)
			break ;
		if (check_value_death(philo))
			break ;
		else if (is_thinking(philo) == 2)
			break ;
	}
	return (0);
}

void	gen_threads(t_philo *philo, t_monitor *monitor)
{
	int	i;

	i = 0;
	if (philo->nb_eat == -1)
		monitor->nbr_eat = 1;
	while (i < philo->nb_philo)
	{
		pthread_create(&philo[i].thread_id, NULL, routine, &philo[i]);
		i++;
	}
}

void	thread_join(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (pthread_join(philo[i].thread_id, NULL) != 0)
			return ;
		i++;
	}
}
