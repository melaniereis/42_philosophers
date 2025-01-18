/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 12:07:30 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void *ft_philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // Add initial delay for even philosophers
    if (philo->id % 2 == 0)
        usleep(1000); // Slight delay for even philosophers

    while (!ft_is_simulation_over(philo->data))
    {
        // If philosopher has eaten enough meals, stop.
        if (philo->data->max_nb_of_meals >= 0 && philo->meals_eaten >= philo->data->max_nb_of_meals)
            break;

        // Eat, sleep, and think in sequence
        if (ft_philo_eat(philo) != SUCCESS)
            break;
        if (ft_philo_sleep(philo) != SUCCESS)
            break;
        if (ft_philo_think(philo) != SUCCESS)
            break;
    }
    return NULL;
}


static int ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL,
                ft_philo_routine, &data->philos[i]) != 0)
            return (ERROR); // Error handling for thread creation
        i++;
    }
    if (pthread_create(&data->monitor, NULL, ft_monitor_routine, data) != 0)
        return (ERROR); // Error handling for monitor thread creation
    return (SUCCESS);
}

static int ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
            return (ERROR); // Error handling for thread joining
        i++;
    }
    if (pthread_join(data->monitor, NULL) != 0)
        return (ERROR); // Error handling for monitor thread joining
    return (SUCCESS);
}

int ft_start_simulation(t_data *data)
{
	if (ft_create_threads(data) != SUCCESS)
        return (ERROR); // Error handling for starting threads
	usleep(100); // Allow threads to start properly
	while (!ft_is_simulation_over(data))
        usleep(1000); // Sleep to reduce CPU usage in main loop
	if (ft_join_threads(data) != SUCCESS)
        return (ERROR); // Error handling for joining threads
	return (SUCCESS);
}
