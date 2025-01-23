/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/23 17:10:31 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Attempt to eat for the philosopher.
 * It first attempts to take the forks. If taking the forks is unsuccessful,
 * it returns an error. Otherwise, it prints a message indicating that the
 * philosopher is eating, sets the last meal time to the current time, and
 * increments the number of meals eaten. Then, it waits for the time to eat
 * specified in the data structure, releases the forks, and returns success.
 * @param philo The philosopher attempting to eat.
 * @return SUCCESS if the philosopher has eaten, ERROR otherwise.
 */
int	ft_philo_eat(t_philo *philo)
{
	if (ft_take_forks(philo) != SUCCESS)
		return (ERROR);
	ft_print_status(philo, "is eating");
	if (pthread_mutex_lock(&philo->meal_mutex) != 0)
		return (ERROR);
	philo->last_meal_time = ft_get_time();
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->meal_mutex) != 0)
		return (ERROR);
	ft_precise_sleep(philo->data->time_to_eat);
	ft_release_forks(philo);
	return (SUCCESS);
}

/**
 * @brief Attempt to sleep for the philosopher.
 * It prints a message indicating that the philosopher is sleeping, waits for
 * the time to sleep specified in the data structure, and returns success.
 * @param philo The philosopher attempting to sleep.
 * @return SUCCESS if the philosopher has slept, ERROR otherwise.
 */
int	ft_philo_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_precise_sleep(philo->data->time_to_sleep);
	return (SUCCESS);
}

/**
 * @brief Attempt to think for the philosopher.
 * It prints a message indicating that the philosopher is thinking and returns
 * success. A small delay is added to prevent busy-waiting.
 * @param philo The philosopher attempting to think.
 * @return SUCCESS if the philosopher has thought, ERROR otherwise.
 */
int	ft_philo_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	usleep(100);
	return (SUCCESS);
}
