/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/20 22:12:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_cleanup(t_data *data)
{
    int i;

    if (data->forks)
    {
        for (i = 0; i < data->nb_of_philos; i++)
            pthread_mutex_destroy(&data->forks[i].mutex);
        free(data->forks);
    }

    if (data->philos)
    {
        for (i = 0; i < data->nb_of_philos; i++)
            pthread_mutex_destroy(&data->philos[i].meal_mutex);
        free(data->philos);
    }

    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->dead_mutex);
    pthread_mutex_destroy(&data->meal_mutex);
}
