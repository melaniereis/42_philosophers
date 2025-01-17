/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:53 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/17 16:49:26 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_is_valid_input(argv, argc) == ERROR)
		return (1);
	if (ft_init_data(&data, argv) == ERROR)
		return (1);
	ft_start_simulation(&data);
	ft_cleanup(&data);
	return (0);
}