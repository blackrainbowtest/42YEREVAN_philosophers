/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utiles_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:48:21 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/20 16:36:38 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    wait_all_processes(t_table *table)
{
    while (!get_bool(&table->sync_lock, &table->all_processes_ready))
        ;
}

bool    all_processes_running(sem_t **sem, long *processes, long philo_nbr)
{
    bool    ret;

    ret = false;
    safe_sem_handle(sem, WAIT);
    if (*processes == philo_nbr)
        ret = true;
    safe_sem_handle(sem, POST);
    return (ret);
}

void    increment_long(sem_t **sem, long *value)
{
    safe_sem_handle(sem, WAIT);
    (*value)++;
    safe_sem_handle(sem, POST);
}
