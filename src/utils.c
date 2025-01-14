/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:11:35 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atol(const char *nptr)
{
	long	result;

	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (result > INT_MAX)
		result = 0;
	return (result);
}

void	ft_print_philo_status(t_philo *philo, const char *status,
		const char *color)
{
	pthread_mutex_lock(&philo->data->check_death_lock);
	if (philo->data->dead_lock_flag)
	{
		pthread_mutex_unlock(&philo->data->check_death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->check_death_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->isdprint == 1)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	printf("%s%ld %d %s%s\n", color, ft_gettime() - philo->data->start_time,
		philo->index + 1, status, END_COLOR);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int ft_check_death(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->meal_lock);
    long current_time = ft_gettime();
    if (current_time - philo->last_meal_time > philo->data->time_to_die * 1000)
    {
        pthread_mutex_unlock(&philo->data->meal_lock);
        ft_set_dead_lock(philo->data);
        ft_print_philo_status(philo, "died", C_RED);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->meal_lock);
    return (0);
}

long ft_gettime(void)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) != 0)
    {
        printf("Error getting time\n");
        return (0);
    }
    return ((current_time.tv_sec * 1000000) + current_time.tv_usec);
}

void ft_usleep(long time_in_us)
{
    long start;

    start = ft_gettime();
    while (ft_gettime() - start < time_in_us)
        usleep(100);
}
