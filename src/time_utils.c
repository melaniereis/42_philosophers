/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/17 16:48:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long ft_gettime(void)
{
    struct timeval current_time;

    if (gettimeofday(&current_time, NULL) != 0)
        return (0);
    return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)); // Convert to milliseconds
}

void	ft_usleep(long time_in_ms)
{
    long	start;
    long	elapsed;

    start = ft_gettime();
    while (1)
    {
        elapsed = ft_gettime() - start;
        if (elapsed >= time_in_ms)
            break ;
        usleep(500);
    }
}