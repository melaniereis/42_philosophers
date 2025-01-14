/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:13:42 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int ft_is_simulation_over(t_data *data)
{
    int result;
    pthread_mutex_lock(&data->dead_lock);
    result = data->dead_lock_flag;
    pthread_mutex_unlock(&data->dead_lock);
    return result;
}

void ft_set_dead_lock(t_data *data)
{
    pthread_mutex_lock(&data->dead_lock);
    data->dead_lock_flag = 1;
    pthread_mutex_unlock(&data->dead_lock);
}


void *ft_philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    ft_set_last_meal_time(philo);
    while (!ft_is_simulation_over(philo->data))
    {
        ft_philo_eat(philo);
        if (ft_is_simulation_over(philo->data) || philo->data->nb_of_philos == 1)
            break;
        ft_philo_sleep(philo);
        if (ft_is_simulation_over(philo->data))
            break;
        ft_print_philo_status(philo, "is thinking", C_BLUE);
    }
    return NULL;
}

void	ft_set_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = ft_gettime();
	pthread_mutex_unlock(&philo->data->meal_lock);
	printf("Philosopher %d last meal time set to %ld\n", philo->index + 1, philo->last_meal_time);
}

void ft_philo_eat(t_philo *philo)
{
    printf("Philosopher %d attempting to eat\n", philo->index + 1);
    
    if (philo->data->nb_of_philos == 1)
    {
        ft_print_philo_status(philo, "has taken a fork", C_YELLOW);
        ft_usleep(philo->data->time_to_die);
        return;
    }
    if (pthread_mutex_lock(&philo->right_fork->fork) != 0)
        return;
    ft_print_philo_status(philo, "has taken a fork", C_YELLOW);
    
    if (pthread_mutex_lock(&philo->left_fork->fork) != 0)
    {
        pthread_mutex_unlock(&philo->right_fork->fork);
        return;
    }
    ft_print_philo_status(philo, "has taken a fork", C_YELLOW);

    ft_print_philo_status(philo, "is eating", C_GREEN);
    ft_usleep(philo->data->time_to_eat);
    ft_set_last_meal_time(philo);

    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);

    printf("Philosopher %d finished eating\n", philo->index + 1);
}

void	ft_philo_sleep(t_philo *philo)
{
	printf("Philosopher %d going to sleep\n", philo->index + 1);
	ft_print_philo_status(philo, "is sleeping", C_YELLOW);
	ft_usleep(philo->data->time_to_sleep);
	printf("Philosopher %d woke up\n", philo->index + 1);
}

void *ft_monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (!ft_is_simulation_over(data))
    {
        i = 0;
        while (i < data->nb_of_philos)
        {
            pthread_mutex_lock(&data->meal_lock);
            if (ft_gettime() - data->philos[i].last_meal_time > data->time_to_die)
            {
                ft_print_philo_status(&data->philos[i], "died", C_RED);
                ft_set_dead_lock(data);
                pthread_mutex_unlock(&data->meal_lock);
                return NULL;
            }
            pthread_mutex_unlock(&data->meal_lock);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}


