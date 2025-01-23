/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:08:31 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/23 15:50:19 by meferraz         ###   ########.fr       */
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
	if (ft_atol(argv[1]) > INT_MAX || ft_atol(argv[2]) > INT_MAX
		|| ft_atol(argv[3]) > INT_MAX || ft_atol(argv[4]) > INT_MAX)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief Convert a string to a long integer.
 * This function takes a string and returns a long integer equivalent.
 * It ignores any leading whitespace and optional sign, and then reads
 * the number until it encounters a non-numeric character.
 * If the number is larger than INT_MAX, it returns 0.
 * @param nptr The string to be converted.
 * @return The long integer equivalent of the string.
 */
long	ft_atol(const char *nptr)
{
	long	result;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+')
		nptr++;
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	if (result > INT_MAX)
		result = 0;
	return (result);
}

/**
 * @brief Prints the status of a philosopher.
 * Prints the timestamp, philosopher ID, and status of the philosopher.
 * If the simulation is over, does nothing.
 * @param philo The philosopher whose status is being printed.
 * @param status The status of the philosopher (e.g. "is eating", "is sleeping", etc.).
 */
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

/**
 * @brief Compares two strings.
 * Compares the first n characters of two strings.
 * If the strings are equal, returns 0.
 * If the first string is lexicographically less than the second, returns a negative value.
 * If the first string is lexicographically greater than the second, returns a positive value.
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n The number of characters to compare.
 * @return 0 if the strings are equal, a negative value if s1 is lexicographically less than s2,
 * a positive value if s1 is lexicographically greater than s2.
 */
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
