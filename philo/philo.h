/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoltura <dpoltura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:24:49 by ppitzini          #+#    #+#             */
/*   Updated: 2024/05/24 12:51:19 by dpoltura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_monitoring
{
	pthread_t		thread;
	int				dead;
	int				meal;
	int				nbr_eat;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}					t_monitor;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				*dead;
	int				*meal;
	int				forks;
	int				start_time;
	int				last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

void				init_forks(t_philo *philo, pthread_mutex_t *forks);
t_philo				*init_struct(char **argv, t_philo *philo,
						t_monitor *monitor, int nb_philo);
void				init_monitor(t_monitor *monitor);
int					check_args(int argc, char **argv);
int					check_value_meal(t_philo *philo);
int					ft_usleep(size_t milliseconds);
int					check_all_death(t_philo *philo, t_monitor *monitor);
int					check_value_death(t_philo *philo);
void				thread_join(t_philo *philo);
void				gen_threads(t_philo *philo, t_monitor *monitor);
int					all_eat(t_philo *philo);
int					ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					is_thinking(t_philo *philo);
int					check_value_meal(t_philo *philo);

#endif
