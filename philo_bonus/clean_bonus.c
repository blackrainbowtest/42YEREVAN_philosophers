/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:02 by root              #+#    #+#             */
/*   Updated: 2025/07/20 16:19:59 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_semaphores(void)
{
	sem_unlink(FORKS);
	sem_unlink(LOCK);
	sem_unlink(CHECK);
	sem_unlink(FINISH);
	sem_unlink(SYNCLOCK);
}

void	clean(t_table *table)
{
	if (table->forks != SEM_FAILED)
		sem_close(table->forks);
	if (table->write_lock != SEM_FAILED)
		sem_close(table->write_lock);
	if (table->meal_check != SEM_FAILED)
		sem_close(table->meal_check);
	if (table->finish != SEM_FAILED)
		sem_close(table->finish);

	free(table->philos);
	cleanup_semaphores();
}