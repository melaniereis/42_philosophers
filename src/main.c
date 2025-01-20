/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:53 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/20 22:10:02 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
    t_data data;

    if (ft_is_valid_input(argv, argc) == ERROR)
    {
        printf("Error: Invalid input\n");
        return (1);
    }

    if (ft_init_data(&data, argc, argv) != SUCCESS)
    {
        printf("Error: Initialization failed\n");
        return (1);
    }

    if (ft_start_simulation(&data) != SUCCESS)
    {
        printf("Error: Simulation failed\n");
        ft_cleanup(&data);
        return (1);
    }

    ft_cleanup(&data);
    return (0);
}

