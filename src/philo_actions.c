/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 09:29:46 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->right_fork->mutex) != 0)
		return (ERROR);
	ft_print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (ERROR);
	}
	ft_print_status(philo, "has taken a fork");
	return (SUCCESS);
}

void	ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

int	ft_philo_eat(t_philo *philo)
{
	if (ft_take_forks(philo) != SUCCESS)
		return (ERROR);
	ft_print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = ft_get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	ft_precise_sleep(philo->data->time_to_eat);
	ft_release_forks(philo);
	return (SUCCESS);
}

int	ft_philo_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_precise_sleep(philo->data->time_to_sleep);
	return (SUCCESS);
}

int	ft_philo_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	return (SUCCESS);
}