/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:23:54 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/22 15:54:46 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int		ft_take_forks_even(t_philo *philo);
static int		ft_take_forks_odd(t_philo *philo);

/**
 * @brief Attempt to take the forks for the philosopher.
 * Handles the edge case where there is only one philosopher, 
 * and retries acquiring forks if initially unsuccessful.
 * @param philo The philosopher attempting to take the forks.
 * @return SUCCESS if forks are acquired, ERROR otherwise.
 */
int	    ft_take_forks(t_philo *philo)
{
	int	retries;

	retries = 0;
	if (philo->data->nb_of_philos == 1)
	{
		if (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
			return (ERROR);
		ft_print_status(philo, "has taken a fork");
		ft_precise_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (ERROR);
	}
	while (retries < MAX_RETRIES)
	{
		if ((philo->id % 2 == 0 && ft_take_forks_even(philo) == SUCCESS)
			|| (philo->id % 2 != 0 && ft_take_forks_odd(philo) == SUCCESS))
			return (SUCCESS);
		usleep(FORK_TIMEOUT);
		retries++;
	}
	return (ERROR);
}

/**
 * @brief Attempt to take forks for an even ID philosopher.
 * Locks the left fork first, then the right fork. If locking the right fork fails,
 * the left fork is unlocked and an error is returned.
 * @param philo The philosopher attempting to take the forks.
 * @return SUCCESS if both forks are acquired, ERROR otherwise.
 */
static int		ft_take_forks_even(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->left_fork->mutex) != 0)
		return (ERROR);
    ft_print_status(philo, "has taken a fork");
	if (pthread_mutex_lock(&philo->right_fork->mutex) != 0)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (ERROR);
	}
	ft_print_status(philo, "has taken a fork");
	return (SUCCESS);
}

/**
 * @brief Attempt to take forks for an odd ID philosopher.
 * Locks the right fork first, then the left fork. If locking the left fork fails,
 * the right fork is unlocked and an error is returned.
 * @param philo The philosopher attempting to take the forks.
 * @return SUCCESS if both forks are acquired, ERROR otherwise.
 */
static int		ft_take_forks_odd(t_philo *philo)
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

/**
 * @brief Release the forks held by a philosopher.
 * Unlocks the left and right forks that the philosopher is holding.
 * @param philo The philosopher releasing the forks.
 */
void		ft_release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
