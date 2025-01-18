/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 11:50:04 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_precise_sleep(long long time_in_ms)
{
	long long	start_time;
	long long	elapsed_time;

	start_time = ft_get_time();
	elapsed_time = 0;

	// Sleep in smaller intervals (e.g., 100 microseconds) to improve precision
	while (elapsed_time < time_in_ms)
	{
		usleep(100); // Sleep for 100 microseconds
		elapsed_time = ft_get_time() - start_time;
	}
}
