/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/20 22:07:23 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

#define MAX_RETRIES 5
#define FORK_TIMEOUT 10000  // Timeout in microseconds (10ms)

int ft_take_forks(t_philo *philo)
{
    int retries = 0;

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
        if (philo->id % 2 == 0)  // Even philosopher: Left fork first
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
        }
        else  // Odd philosopher: Right fork first
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
        }
        return SUCCESS;  // Success: both forks acquired

        // Retry logic
        usleep(FORK_TIMEOUT);  // Retry after a short timeout
        retries++;
    }

    return ERROR;  // Return error if retries exceeded
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
	ft_precise_sleep(philo->data->time_to_sleep); // Simulate sleeping time
	return (SUCCESS);
}

int	ft_philo_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	return (SUCCESS); // No specific actions needed for thinking
}
