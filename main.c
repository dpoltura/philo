/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:45:46 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/24 12:52:37 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int				nb_philo;
	t_philo			*philo;
	t_monitor		monitor;
	pthread_mutex_t	*forks;

	philo = NULL;
	if (check_args(argc, argv))
		return (1);
	init_monitor(&monitor);
	nb_philo = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * nb_philo);
	philo = init_struct(argv, philo, &monitor, nb_philo);
	forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	init_forks(philo, forks);
	gen_threads(philo, &monitor);
	while (1)
	{
		if (check_all_death(philo, &monitor))
			break ;
	}
	thread_join(philo);
	free(forks);
	free(philo);
	return (0);
}
