/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/23 16:56:13 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Get the current time in milliseconds.
 * This function uses the gettimeofday function to retrieve the current time,
 * then converts it to milliseconds.
 * @return The current time in milliseconds.
 */
long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

/**
 * @brief Sleep for a precise amount of time in milliseconds.
 * This function uses a loop to repeatedly check the elapsed time
 * and calls `usleep` to wait in small increments, ensuring accurate sleep time.
 * @param time_in_ms The amount of time to sleep in milliseconds.
 */
void	ft_precise_sleep(long long time_in_ms)
{
	long long	start_time;
	long long	elapsed_time;

	start_time = ft_get_time();
	elapsed_time = 0;
	while (elapsed_time < time_in_ms)
	{
		usleep(500);
		elapsed_time = ft_get_time() - start_time;
	}
}
