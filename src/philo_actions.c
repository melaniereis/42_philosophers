/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:59:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_status ft_take_forks(t_philo *philo);
void ft_release_forks(t_philo *philo);

void *ft_philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!ft_is_simulation_over(philo->data))
    {
        if (ft_check_philosopher_death(philo->data, philo->index))
            break;
        if (ft_philo_eat(philo) == ERROR)
            break;
        if (ft_philo_sleep(philo) == ERROR)
            break;
        if (ft_philo_think(philo) == ERROR)
            break;
    }
    return (NULL);
}



t_status	ft_philo_eat(t_philo *philo)
{
	if (ft_take_forks(philo) == ERROR)
		return (ERROR);
	ft_print_philo_status(philo, "is eating", C_GREEN);
	ft_set_last_meal_time(philo);
	ft_usleep(philo->data->time_to_eat);
	ft_release_forks(philo);
	philo->meals_eaten++;
	return (SUCCESS);
}

t_status	ft_philo_sleep(t_philo *philo)
{
	ft_print_philo_status(philo, "is sleeping", C_BLUE);
	ft_usleep(philo->data->time_to_sleep);
	return (SUCCESS);
}

t_status	ft_philo_think(t_philo *philo)
{
	ft_print_philo_status(philo, "is thinking", C_YELLOW);
	ft_usleep((philo->data->time_to_die - philo->data->time_to_eat
			- philo->data->time_to_sleep) / 2);
	return (SUCCESS);
}
t_status ft_take_forks(t_philo *philo)
{
    if (philo->index % 2 == 0)
    {
        pthread_mutex_lock(&philo->right_fork->fork);
        ft_print_philo_status(philo, "has taken a fork", C_CYAN);
        pthread_mutex_lock(&philo->left_fork->fork);
        ft_print_philo_status(philo, "has taken a fork", C_CYAN);
    }
    else
    {
        pthread_mutex_lock(&philo->left_fork->fork);
        ft_print_philo_status(philo, "has taken a fork", C_CYAN);
        pthread_mutex_lock(&philo->right_fork->fork);
        ft_print_philo_status(philo, "has taken a fork", C_CYAN);
    }
    return SUCCESS;
}

void ft_release_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
    ft_print_philo_status(philo, "has released forks", C_MAGENTA);
}

void	ft_set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = ft_gettime() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meal_lock);
}
