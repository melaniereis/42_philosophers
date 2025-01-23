/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/23 17:00:37 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int		ft_create_threads(t_data *data);
static void		*ft_philo_routine(void *arg);
static int		ft_join_threads(t_data *data);

/**
 * @brief Starts the simulation by creating the threads for the philosophers
 * and the monitor, and waits for them to finish.
 * @param data The data structure containing the information of the philosophers.
 * @return 0 if the simulation runs successfully, 1 otherwise.
 */
int		ft_start_simulation(t_data *data)
{
	if (ft_create_threads(data) != SUCCESS)
	{
		ft_cleanup(data);
		return (ERROR);
	}
	usleep(100);
	while (!ft_is_simulation_over(data))
		usleep(1000);
	if (ft_join_threads(data) != SUCCESS)
	{
		ft_cleanup(data);
		return (ERROR);
	}
	return (SUCCESS);
}

/**
 * @brief Creates the threads for the philosophers and the monitor.
 * @param data The data structure containing the information of the philosophers.
 * @return 0 if the threads are created successfully, 1 otherwise.
 */
static int		ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				ft_philo_routine, &data->philos[i]) != 0)
			return (ERROR);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, ft_monitor_routine, data) != 0)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief The routine for each philosopher thread.
 * Each philosopher alternates between eating, sleeping, and thinking,
 * until the simulation is over.
 * @param arg The philosopher structure passed as an argument.
 * @return NULL when the routine ends.
 */
static void		*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_is_simulation_over(philo->data))
	{
		if (ft_philo_eat(philo) != SUCCESS || ft_is_simulation_over(philo->data))
			break ;
		if (ft_philo_sleep(philo) != SUCCESS || ft_is_simulation_over(philo->data))
			break ;
		if (ft_philo_think(philo) != SUCCESS || ft_is_simulation_over(philo->data))
			break ;
	}
	return (NULL);
}

/**
 * @brief Wait for all philosopher threads to finish and join them.
 * @param data The data structure containing the information of the philosophers.
 * @return 0 if all threads are joined successfully, 1 otherwise.
 */
static int		ft_join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (ERROR);
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (ERROR);
	return (SUCCESS);
}
