/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:28:02 by dpoltura          #+#    #+#             */
/*   Updated: 2024/05/24 12:52:03 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_death(t_philo *philo, int i)
{
	int	elapsed_time;

	elapsed_time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf("%d %d died\n", elapsed_time, philo[i].id);
	pthread_mutex_unlock(philo->write_lock);
	*philo[i].dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	check_all_death(t_philo *philo, t_monitor *monitor)
{
	int	i;
	int	time_since_last_meal;

	i = 0;
	while (i < philo->nb_philo)
	{
		if (monitor->nbr_eat == 0 && all_eat(philo))
			return (1);
		pthread_mutex_lock(philo->meal_lock);
		time_since_last_meal = get_current_time() - philo[i].last_meal;
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->dead_lock);
		if (time_since_last_meal > philo[i].time_to_die)
			return (handle_death(philo, i));
		pthread_mutex_unlock(philo->dead_lock);
		if (i == philo->nb_philo)
			i = 0;
		else
			i++;
	}
	return (0);
}

int	check_value_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
