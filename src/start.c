/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:55:57 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_join_threads(t_data *data);

void	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&ft_philo_routine, &data->philos[i]) != 0)
			return ;
		usleep(100);
		i++;
	}
}

void	ft_start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	data->start_time = ft_gettime();
	ft_create_threads(data);
	if (pthread_create(&monitor_thread, NULL, ft_monitor_routine, data) != 0)
		return ;
	pthread_join(monitor_thread, NULL);
	ft_join_threads(data);
}

static void	ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}