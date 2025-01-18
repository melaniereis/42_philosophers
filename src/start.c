/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 09:35:11 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_is_simulation_over(philo->data))
	{
		if (ft_philo_eat(philo) != SUCCESS)
			break ;
		if (ft_philo_sleep(philo) != SUCCESS)
			break ;
		if (ft_philo_think(philo) != SUCCESS)
			break ;
	}
	return (NULL);
}

static int	ft_create_threads(t_data *data)
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

static int	ft_join_threads(t_data *data)
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

int	ft_start_simulation(t_data *data)
{
	if (ft_create_threads(data) != SUCCESS)
		return (ERROR);
	if (ft_join_threads(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
