/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:21:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 11:10:40 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

# define C_RED "\033[31m"
# define C_GREEN "\033[32m"
# define C_YELLOW "\033[33m"
# define C_BLUE "\033[34m"
# define C_MAGENTA "\033[35m"
# define C_CYAN "\033[36m"
# define C_WHITE "\033[37m"
# define C_RESET "\033[0m"

typedef int	t_status;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_nb_of_meals;
	t_fork			*forks;
	t_philo			*philos;
	long long		start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	volatile int	dead_flag;
	pthread_mutex_t	meal_mutex;
	pthread_t		monitor;
}	t_data;

int			ft_init_data(t_data *data, int argc, char **argv);
int			ft_take_forks(t_philo *philo);
void		ft_release_forks(t_philo *philo);
int			ft_philo_eat(t_philo *philo);
int			ft_philo_sleep(t_philo *philo);
int			ft_philo_think(t_philo *philo);
void		*ft_monitor_routine(void *arg);
int			ft_is_simulation_over(t_data *data);
void		ft_set_dead_flag(t_data *data);
long long	ft_get_time(void);
void		ft_precise_sleep(long long time_in_ms);
void		ft_print_status(t_philo *philo, const char *status);
void		ft_cleanup(t_data *data);
int			ft_start_simulation(t_data *data);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_status	ft_is_valid_input(char **argv, int argc);
long		ft_atol(const char *nptr);

#endif
