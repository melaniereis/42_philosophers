/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:37:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:58:12 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_mutexes(t_data *data);
static void	init_philos(t_data *data);

t_status	ft_is_valid_input(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (ERROR);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[2]) <= 0
		|| ft_atol(argv[3]) <= 0 || ft_atol(argv[4]) <= 0)
		return (ERROR);
	if (argc == 6 && ft_atol(argv[5]) <= 0)
		return (ERROR);
	return (SUCCESS);
}
t_status	ft_init_data(t_data *data, char **argv)
{
	data->nb_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	data->max_nb_of_meals = (argv[5]) ? ft_atol(argv[5]) : -1;
	data->dead_lock_flag = 0;
	data->isdprint = 0;
	init_mutexes(data);
	data->forks = malloc(sizeof(t_fork) * data->nb_of_philos);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->forks || !data->philos)
		return (ERROR);
	init_philos(data);
	return (SUCCESS);
}

static void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->check_death_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

static void	init_philos(t_data *data)
{
	int	i;
    long start_time;

	i = 0;
    start_time = ft_gettime();
	while (i < data->nb_of_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->philos[i].index = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].state = THINKING;
		data->philos[i].data = data;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nb_of_philos];
        data->philos[i].last_meal_time = start_time;
		i++;
	}
    data->start_time = start_time;
}
