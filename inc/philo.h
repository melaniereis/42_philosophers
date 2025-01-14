/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:21:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:50:11 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define C_RED "\033[31m"
# define C_GREEN "\033[32m"
# define C_YELLOW "\033[33m"
# define C_BLUE "\033[34m"
# define C_MAGENTA "\033[35m"
# define C_CYAN "\033[36m"
# define END_COLOR "\033[0m"

typedef pthread_mutex_t	t_mtx;

typedef enum e_status
{
	SUCCESS = 0,
	ERROR = 1
}	t_status;

typedef enum e_philo_state
{
	THINKING = 0,
	EATING = 1,
	SLEEPING = 2,
	DYING = 3
}	t_philo_state;

typedef struct s_fork
{
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	int				index;
	int				meals_eaten;
	long			last_meal_time;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread;
	int				is_eating;
	t_philo_state	state;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long			nb_of_philos;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			max_nb_of_meals;
	t_fork			*forks;
	t_philo			*philos;
	long			start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	check_death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	int				dead_lock_flag;
	int				isdprint;
}	t_data;

// init.c
t_status	ft_is_valid_input(char **argv, int argc);
t_status	ft_init_data(t_data *data, char **argv);

// philo_actions.c
void		*ft_philo_routine(void *arg);
t_status	ft_philo_eat(t_philo *philo);
t_status	ft_philo_sleep(t_philo *philo);
t_status	ft_philo_think(t_philo *philo);
t_status	ft_take_forks(t_philo *philo);
void		ft_release_forks(t_philo *philo);
void		ft_set_last_meal_time(t_philo *philo);

// monitor.c
void		*ft_monitor_routine(void *arg);
int			ft_check_philosopher_death(t_data *data, int i);
int			ft_check_meals_eaten(t_data *data);
int			ft_is_simulation_over(t_data *data);
void		ft_set_dead_lock(t_data *data);

// utils.c
long		ft_atol(const char *nptr);
void		ft_print_philo_status(t_philo *philo, const char *status,
				const char *color);

// time_utils.c
long		ft_gettime(void);
void		ft_usleep(long time_in_us);

// cleanup.c
void		ft_cleanup(t_data *data);
void		ft_free_data(t_data *data);

// start.c
void		ft_start_simulation(t_data *data);
void		ft_create_threads(t_data *data);

#endif
