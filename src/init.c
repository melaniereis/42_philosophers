/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:37:34 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 11:03:16 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->dead_mutex, NULL) != 0
		|| pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (ERROR);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0
			|| pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = ft_get_time();
		data->philos[i].data = data;
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nb_of_philos];
		i++;
	}
	return (SUCCESS);
}

static int	ft_init_data_values(t_data *data, int argc, char **argv)
{
	data->nb_of_philos = (int)ft_atol(argv[1]);
	data->time_to_die = (int)ft_atol(argv[2]);
	data->time_to_eat = (int)ft_atol(argv[3]);
	data->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		data->max_nb_of_meals = (int)ft_atol(argv[5]);
	else
		data->max_nb_of_meals = -1;
	data->dead_flag = 0;
	data->start_time = ft_get_time();
	return (SUCCESS);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	if (ft_init_data_values(data, argc, argv) != SUCCESS)
		return (ERROR);
	data->forks = malloc(sizeof(t_fork) * data->nb_of_philos);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->forks || !data->philos)
		return (ERROR);
	if (ft_init_mutexes(data) != SUCCESS || ft_init_philos(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
