/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:53 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/18 09:16:52 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_is_valid_input(argv, argc) == ERROR)
		return (printf("Error: Invalid input\n"));
	if (ft_init_data(&data, argc, argv) != SUCCESS)
		return (printf("Error: Initialization failed\n"));
	if (ft_start_simulation(&data) != SUCCESS)
		return (printf("Error: Simulation failed\n"));
	ft_cleanup(&data);
	return (0);
}