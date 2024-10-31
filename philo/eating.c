/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:25:44 by dpoltura          #+#    #+#             */
/*   Updated: 2024/05/24 12:56:42 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eat(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(philo->meal_lock);
	while (i < philo->nb_philo)
	{
		if (philo[i].nb_eat > 0)
		{
			pthread_mutex_unlock(philo->meal_lock);
			return (0);
		}
		i++;
	}
	*philo->meal = 1;
	pthread_mutex_unlock(philo->meal_lock);
	return (1);
}

static void	eating(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->nb_eat--;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	print_eating(t_philo *philo)
{
	int	elapsed_time;

	if (!(check_value_death(philo)))
	{
		pthread_mutex_lock(philo->write_lock);
		elapsed_time = get_current_time() - philo->start_time;
		printf("%d %d is eating\n", elapsed_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
	}
}

static void	choose_fork(t_philo *philo, pthread_mutex_t **first_fork,
		pthread_mutex_t **second_fork)
{
	if (philo->l_fork < philo->r_fork)
	{
		*first_fork = philo->l_fork;
		*second_fork = philo->r_fork;
	}
	else
	{
		*first_fork = philo->r_fork;
		*second_fork = philo->l_fork;
	}
}

int	is_eating(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	choose_fork(philo, &first_fork, &second_fork);
	if (check_value_death(philo) == 1 || check_value_meal(philo) == 1)
		return (2);
	pthread_mutex_lock(first_fork);
	if (check_value_death(philo) == 1)
	{
		pthread_mutex_unlock(first_fork);
		return (2);
	}
	pthread_mutex_lock(second_fork);
	if (check_value_death(philo) == 1)
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (2);
	}
	print_eating(philo);
	eating(philo, first_fork, second_fork);
	return (0);
}
