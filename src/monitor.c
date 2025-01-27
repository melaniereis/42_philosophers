/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/27 17:39:51 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_check_death(t_data *data, int i);
static int	ft_all_ate_enough(t_data *data);

/**
 * @brief The routine for the monitor thread.
 * The monitor thread checks every 1ms if a philosopher has died or if all
 * philosophers have eaten enough.
 * @param arg The data structure containing the information of the philosophers.
 * @return NULL if the simulation is over.
 */
void	*ft_monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!ft_is_simulation_over(data))
	{
		i = 0;
		while (i < data->nb_of_philos && !ft_is_simulation_over(data))
		{
			if (ft_check_death(data, i))
				return (NULL);
			i++;
		}
		if (ft_all_ate_enough(data))
			ft_set_dead_flag(data);
		usleep(5000);
	}
	return (NULL);
}

/**
 * @brief Check if the simulation is over.
 * The simulation is considered over if the dead flag is set or if all
 * philosophers have eaten the maximum number of meals (if specified).
 * @param data The data structure containing the simulation state.
 * @return 1 if the simulation is over, 0 otherwise.
 */
int	ft_is_simulation_over(t_data *data)
{
	int	result;
	int	i;
	int	all_ate_enough;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	if (data->max_nb_of_meals >= 0)
	{
		all_ate_enough = 1;
		i = 0;
		while (i < data->nb_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			if (data->philos[i].meals_eaten < data->max_nb_of_meals)
				all_ate_enough = 0;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if (!all_ate_enough)
				break ;
			i++;
		}
		return (result || all_ate_enough);
	}
	return (result);
}

/**
 * @brief Check if a philosopher should die.
 * @param data The data structure containing the philosopher's information.
 * @param i The index of the philosopher to check.
 * @return 1 if the philosopher should die, 0 otherwise.
 */
static int	ft_check_death(t_data *data, int i)
{
	long long	current_time;
	int			should_die;

	should_die = 0;
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	current_time = ft_get_time();
	if (current_time - data->philos[i].last_meal_time > data->time_to_die)
		should_die = 1;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if (should_die)
	{
		ft_print_status(&data->philos[i], "died");
		ft_set_dead_flag(data);
		return (1);
	}
	return (0);
}

/**
 * @brief Set the dead flag.
 * @param data The data structure containing the dead flag.
 */
void	ft_set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

/**
 * @brief Check if all philosophers have eaten enough.
 * @param data The data structure containing the information of the philosophers.
 * @return 1 if all philosophers have eaten enough, 0 otherwise.
 */
static int	ft_all_ate_enough(t_data *data)
{
	int	i;

	if (data->max_nb_of_meals < 0)
		return (0);
	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->max_nb_of_meals)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}
