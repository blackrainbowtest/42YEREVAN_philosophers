/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:58:34 by root              #+#    #+#             */
/*   Updated: 2025/07/20 16:22:52 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Initializes philosopher data: ID, table reference, etc.
 * 
 * @param table Pointer to the simulation table
 */
static void	init_philosophers(t_table *table)
{
	int	i;
	
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	i = -1;
	while (++i < table->philo_nbr)
	{
		t_philo *philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->last_meal_time = 0;
		philo->table = table;
		philo->full = false;
	}
}

/**
 * @brief Creates and initializes all required named semaphores.
 * 
 * @param table Pointer to the simulation table
 */
static void	init_semaphores(t_table *table)
{
	cleanup_semaphores();
	table->ready_count = 0;
	table->forks = sem_open(FORKS, O_CREAT | O_EXCL, 0644, table->philo_nbr);
	table->write_lock = sem_open(LOCK, O_CREAT | O_EXCL, 0644, 1);
	table->meal_check = sem_open(CHECK, O_CREAT | O_EXCL, 0644, 1);
	table->finish = sem_open(FINISH, O_CREAT | O_EXCL, 0644, 0);
	table->sync_lock = sem_open(SYNCLOCK, O_CREAT | O_EXCL, 0644, 1);
	table->all_processes_ready = false;
	table->end_simulation = false;
	if (table->forks == SEM_FAILED || table->write_lock == SEM_FAILED
		|| table->meal_check == SEM_FAILED || table->finish == SEM_FAILED)
		error_exit("sem_open failed");
}

/**
 * @brief High-level initialization of table and philosophers.
 * 
 * @param table Main simulation structure (must already contain parsed values)
 */
void	data_init(t_table *table)
{
	init_semaphores(table);
	init_philosophers(table);
}