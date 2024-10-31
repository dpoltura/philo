/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:30:28 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/23 16:49:15 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] != '\0')
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = sign * -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + str[i] - 48;
			i++;
		}
		return (result * sign);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	int	elapsed_time;

	if (!(check_value_death(philo)))
	{
		pthread_mutex_lock(philo->write_lock);
		elapsed_time = get_current_time() - philo->start_time;
		printf("%d %d is sleeping\n", elapsed_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
	}
	else
		return (2);
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	is_thinking(t_philo *philo)
{
	int	elapsed_time;

	if (!(check_value_death(philo)))
	{
		pthread_mutex_lock(philo->write_lock);
		elapsed_time = get_current_time() - philo->start_time;
		printf("%d %d is thinking\n", elapsed_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
	}
	else
		return (2);
	return (0);
}
