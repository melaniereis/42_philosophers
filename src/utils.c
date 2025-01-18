/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 09:28:22 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_status	ft_is_valid_input(char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (ERROR);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[2]) <= 0
		|| ft_atol(argv[3]) <= 0 || ft_atol(argv[4]) <= 0)
		return (ERROR);
	if (argc == 6 && ft_atol(argv[5]) <= 0)
		return (ERROR);
	return (SUCCESS);
}

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

void	ft_print_status(t_philo *philo, const char *status)
{
	long long	timestamp;
	const char	*color;

	if (ft_is_simulation_over(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = ft_get_time() - philo->data->start_time;
	if (ft_strncmp(status, "has taken a fork", 16) == 0)
		color = C_CYAN;
	else if (ft_strncmp(status, "is eating", 9) == 0)
		color = C_GREEN;
	else if (ft_strncmp(status, "is sleeping", 11) == 0)
		color = C_BLUE;
	else if (ft_strncmp(status, "is thinking", 11) == 0)
		color = C_YELLOW;
	else if (ft_strncmp(status, "died", 4) == 0)
		color = C_RED;
	else
		color = C_WHITE;
	printf("%s%lld %d %s%s\n", color, timestamp, philo->id, status, C_RESET);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}