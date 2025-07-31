/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:44:51 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/31 19:44:51 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(sem_t **sem, bool *dest, bool value)
{
	safe_sem_handle(sem, WAIT);
	*dest = value;
	safe_sem_handle(sem, POST);
}

bool	get_bool(sem_t **sem, bool *value)
{
	bool	ret;

	safe_sem_handle(sem, WAIT);
	ret = *value;
	safe_sem_handle(sem, POST);
	return (ret);
}

void	set_long(sem_t **sem, long *dest, long value)
{
	safe_sem_handle(sem, WAIT);
	*dest = value;
	safe_sem_handle(sem, POST);
}

long	get_long(sem_t **sem, long *value)
{
	long	ret;

	safe_sem_handle(sem, WAIT);
	ret = *value;
	safe_sem_handle(sem, POST);
	return (ret);
}

bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->sem->sync_sem, &table->end_simulation));
}
