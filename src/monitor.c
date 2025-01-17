/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/17 16:47:25 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void *ft_monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!ft_is_simulation_over(data))
    {
        i = 0;
        while (i < data->nb_of_philos && !ft_is_simulation_over(data))
        {
            if (ft_check_philosopher_death(data, i))
            {
                ft_set_dead_lock(data);
                return (NULL);
            }
            i++;
        }
        if (data->max_nb_of_meals > 0 && ft_all_ate_enough(data))
        {
            ft_set_dead_lock(data);
            return (NULL);
        }
        usleep(100);
    }
    return (NULL);
}

int ft_check_philosopher_death(t_data *data, int i)
{
    long current_time, last_meal_time, time_since_last_meal;

    current_time = ft_gettime() - data->start_time;
    pthread_mutex_lock(&data->philos[i].time_mutex);
    last_meal_time = data->philos[i].last_meal_time;
    pthread_mutex_unlock(&data->philos[i].time_mutex);
    time_since_last_meal = current_time - last_meal_time;
   //printf("Checking philosopher %d: current time: %ld, last meal: %ld, time since last meal: %ld\n", i, current_time, last_meal_time, time_since_last_meal);
    //printf("Death check triggered for philosopher %d: time_since_last_meal = %ld, time_to_die = %ld\n",
          // i, time_since_last_meal, data->time_to_die);
    if (time_since_last_meal >= data->time_to_die)
    {
        pthread_mutex_lock(&data->dead_lock);
        if (!data->dead_lock_flag)
        {
            ft_print_philo_status(&data->philos[i], "died", C_RED);
            ft_set_dead_lock(data);
        }
        pthread_mutex_unlock(&data->dead_lock);
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