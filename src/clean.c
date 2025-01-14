/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 18:07:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->check_death_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
}
