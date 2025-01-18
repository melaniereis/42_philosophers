/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 11:46:14 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

void ft_cleanup(t_data *data)
{
    if (data->forks)
        free(data->forks);
    if (data->philos)
        free(data->philos);
    ft_destroy_mutexes(data);
}
