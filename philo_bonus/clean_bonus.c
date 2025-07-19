/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:02 by root              #+#    #+#             */
/*   Updated: 2025/07/19 16:48:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Closes and unlinks all used named semaphores.
 */
void	cleanup_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/meal_check");
	sem_unlink("/finish");
}

/**
 * @brief Releases all resources: semaphores, memory, etc.
 * 
 * @param table Main simulation structure
 */
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