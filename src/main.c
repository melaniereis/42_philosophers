/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:22:53 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/07 17:24:55 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int main(int argc, char **argv)
{
    t_data data;
    if (argc == 5 || argc == 6)
    {
        if (ft_atol(argv[1]) == 0 || ft_atol(argv[2]) == 0 
        || ft_atol(argv[3]) == 0 || ft_atol(argv[4]) == 0 
        || (argv[5] && ft_atol(argv[5]) == 0))
            {
                printf("Invalid arguments..\n
                        It should be numbers bigger 
                        than 0 and less than INT_MAX\n");
                return (1);
            }
        init_data(&data);
        start_meal(&data); 
    }
    else
    {
        printf("Invalid number of arguments..\n
                 It should be something like: ./philo 6 800 200 200 [4]\n");
        return (1);
    }
    return (0);
}
