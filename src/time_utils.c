/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/14 21:59:23 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_gettime(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != 0)
		return (0);
	return ((current_time.tv_sec * 1000000) + current_time.tv_usec);
}

void ft_usleep(long time_in_us)
{
    long start;
    long end;

    start = ft_gettime();
    end = start + time_in_us;
    while (ft_gettime() < end)
        usleep(100);
}
