/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:21:06 by meferraz          #+#    #+#             */
/*   Updated: 2025/01/07 17:24:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef pthread_mutex_t t_mtx;

typedef struct s_fork
{
    t_mtx   fork;
}   t_fork;

typedef struct s_philo
{
    int index;
    int meals_eaten;
    t_fork  *right_fork;
    t_fork  *left_fork;
}   t_philo;

typedef struct s_data
{
    long    nb_of_philos;
    long    time_to_die;
    long    time_to_sleep;
    long    time_to_eat;
    long    max_nb_of_meals;
    t_fork  *fork;
    t_philo *philos;
}   t_data;

long	ft_atol(const char *nptr);

#endif