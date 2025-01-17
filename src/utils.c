/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/17 16:48:41 by meferraz         ###   ########.fr       */
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

void ft_print_philo_status(t_philo *philo, const char *status, const char *color)
{
    long timestamp;
    
    pthread_mutex_lock(&philo->data->print_lock);
    if (!ft_is_simulation_over(philo->data)) 
    {
        timestamp = ft_gettime() - philo->data->start_time;
        printf("%s%ld %d %s%s\n", color, timestamp, philo->index + 1, status, END_COLOR);
    }
    pthread_mutex_unlock(&philo->data->print_lock);
}