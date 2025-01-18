/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 09:29:07 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_death(t_data *data, int i)
{
	long long	current_time;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	current_time = ft_get_time();
	if (current_time - data->philos[i].last_meal_time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		ft_print_status(&data->philos[i], "died");
		ft_set_dead_flag(data);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	return (0);
}

int	ft_is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->dead_mutex);
	result = data->dead_flag;
	pthread_mutex_unlock(&data->dead_mutex);
	return (result);
}

void	ft_set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}

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
			if (ft_check_death(data, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}