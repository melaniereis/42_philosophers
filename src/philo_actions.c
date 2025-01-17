/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/17 16:47:51 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_status ft_take_forks(t_philo *philo);
void ft_release_forks(t_philo *philo);
int	ft_all_ate_enough(t_data *data);

void *ft_philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->index % 2 != 0)
        usleep(1000);
    while (!ft_is_simulation_over(philo->data))
    {
        if (ft_philo_think(philo) == ERROR ||
            ft_philo_eat(philo) == ERROR ||
            ft_philo_sleep(philo) == ERROR)
            break;
        if (ft_is_simulation_over(philo->data))
            break;
    }
    return (NULL);
}

int ft_should_terminate(t_data *data)
{
    return (ft_is_simulation_over(data) || 
            (data->max_nb_of_meals > 0 && ft_all_ate_enough(data)));
}

int ft_all_ate_enough(t_data *data)
{
    int i;
    int all_ate_enough;

    if (data->max_nb_of_meals < 0)
        return (0);
    i = 0;
    all_ate_enough = 1;
    pthread_mutex_lock(&data->meal_lock);
    while (i < data->nb_of_philos)
    {
        if (data->philos[i].meals_eaten < data->max_nb_of_meals)
        {
            all_ate_enough = 0;
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&data->meal_lock);
    return (all_ate_enough);
}

t_status ft_philo_eat(t_philo *philo)
{
    if (ft_is_simulation_over(philo->data))
        return (ERROR);

    if (ft_take_forks(philo) == ERROR)
        return (ERROR);
    
    ft_print_philo_status(philo, "is eating", C_GREEN);
    ft_usleep(philo->data->time_to_eat);
    ft_set_last_meal_time(philo); 
    ft_release_forks(philo);
    
    pthread_mutex_lock(&philo->data->meal_lock);
    philo->meals_eaten++;
    if (philo->meals_eaten == philo->data->max_nb_of_meals)
    {
        if (ft_all_ate_enough(philo->data))
            ft_set_dead_lock(philo->data);
    }
    pthread_mutex_unlock(&philo->data->meal_lock);
    
    return (SUCCESS);
}

t_status	ft_philo_sleep(t_philo *philo)
{
	ft_print_philo_status(philo, "is sleeping", C_BLUE);
	ft_usleep(philo->data->time_to_sleep);
	return (SUCCESS);
}

t_status ft_philo_think(t_philo *philo)
{
    ft_print_philo_status(philo, "is thinking", C_YELLOW);
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
        if (philo->data->nb_of_philos > 1)
        {
            pthread_mutex_lock(&philo->right_fork->fork);
            ft_print_philo_status(philo, "has taken a fork", C_CYAN);
        }
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
    pthread_mutex_lock(&philo->time_mutex);
    philo->last_meal_time = ft_gettime() - philo->data->start_time;
    pthread_mutex_unlock(&philo->time_mutex);
}