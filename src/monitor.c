/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:58:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!ft_is_simulation_over(data))
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (ft_check_philosopher_death(data, i))
				return (NULL);
			if (ft_check_meals_eaten(data))
				return (NULL);
			i++;
		}
		ft_usleep(1000);
	}
	return (NULL);
}

int ft_check_philosopher_death(t_data *data, int i)
{
    long current_time;

    pthread_mutex_lock(&data->meal_lock);
    current_time = ft_gettime();
    if (current_time - data->philos[i].last_meal_time > data->time_to_die)
    {
        ft_print_philo_status(&data->philos[i], "died", C_RED);
        ft_set_dead_lock(data);
        pthread_mutex_unlock(&data->meal_lock);
        return (1);
    }
    pthread_mutex_unlock(&data->meal_lock);
    return (0);
}

int	ft_check_meals_eaten(t_data *data)
{
	int	i;
	int	all_ate_enough;

	if (data->max_nb_of_meals == -1)
		return (0);
	i = 0;
	all_ate_enough = 1;
	while (i < data->nb_of_philos)
	{
		if (data->philos[i].meals_eaten < data->max_nb_of_meals)
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	if (all_ate_enough)
	{
		ft_set_dead_lock(data);
		return (1);
	}
	return (0);
}

int	ft_is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_lock);
	result = data->dead_lock_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (result);
}

void	ft_set_dead_lock(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_lock_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}
