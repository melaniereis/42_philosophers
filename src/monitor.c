/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/20 22:10:25 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int ft_check_death(t_data *data, int i)
{
    long long current_time;
    int should_die = 0;

    pthread_mutex_lock(&data->philos[i].meal_mutex);
    current_time = ft_get_time();
    if (current_time - data->philos[i].last_meal_time > data->time_to_die)
        should_die = 1;
    pthread_mutex_unlock(&data->philos[i].meal_mutex);

    if (should_die)
    {
        ft_print_status(&data->philos[i], "died");
        ft_set_dead_flag(data);
        return 1;
    }
    return 0;
}

int	ft_is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
    if (data->max_nb_of_meals >= 0)
    {
        int i = 0;
        while (i < data->nb_of_philos)
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            if (data->philos[i].meals_eaten < data->max_nb_of_meals)
            {
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
                return result; // Still not done
            }
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            i++;
        }
        return 1; // All philosophers have eaten enough meals
    }
	return (result);
}

void	ft_set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

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

void *ft_monitor_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!ft_is_simulation_over(data))
    {
        i = 0;
        while (i < data->nb_of_philos && !ft_is_simulation_over(data))
        {
            if (ft_check_death(data, i))
                return NULL;
            i++;
        }
        if (ft_all_ate_enough(data))
            ft_set_dead_flag(data);
        usleep(1000); // Sleep to reduce CPU usage
    }
    return NULL;
}

