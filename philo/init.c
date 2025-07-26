/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:12:04 by root              #+#    #+#             */
/*   Updated: 2025/07/14 23:14:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Assigns forks to a philosopher in a specific order to prevent 
 * deadlocks.
 * 
 * This function sets the pointers to the left and right forks for the given
 * philosopher. The order of fork acquisition is reversed for even-numbered
 * philosophers to break circular wait conditions and avoid deadlocks.
 * 
 * - Odd philosophers take the right fork first, then the left.
 * - Even philosophers take the left fork first, then the right.
 * 
 * @param philo Pointer to the philosopher being initialized.
 * @param forks Array of all fork mutex structures.
 * @param philo_position Index of the philosopher in the array (0-based).
 * 
 * @note This fork-ordering strategy is a classic solution to the Dining
 * Philosophers problem for avoiding deadlocks.
 */
static void	assign_fork(t_philo *philo, t_fork *forks,
		int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

/**
 * @brief Initializes each philosopher in the simulation.
 * 
 * Sets up the internal state of each philosopher, including their unique ID,
 * meal counters, and reference to the main table structure. Also initializes
 * a per-philosopher mutex to protect individual data and assigns forks in a
 * deadlock-safe order.
 * 
 * @param table Pointer to the main simulation table containing all philosophers.
 * 
 * @note This function should be called after memory allocation and table
 * parameter parsing, but before starting the simulation.
 * 
 * @see assign_fork(), safe_mutex_handle()
 */
static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_fork(philo, table->forks, i);
	}
}

/**
 * @brief Initializes core simulation data structures.
 * 
 * Allocates memory for philosophers and forks, initializes mutexes for 
 * table-level and fork-level synchronization, and sets initial flags and 
 * counters.
 * 
 * Each fork receives a unique ID and a mutex for access control. After 
 * setting up shared structures, the individual philosopher structures 
 * are initialized as well.
 * 
 * @param table Pointer to the main simulation table.
 * 
 * @note This function must be called before launching any threads. All mutexes
 * are created using `safe_mutex_handle`, and memory is allocated via 
 * `safe_malloc`.
 * 
 * @see philo_init(), safe_malloc(), safe_mutex_handle()
 */
void	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_number = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (++i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
