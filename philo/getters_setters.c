/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:40:17 by root              #+#    #+#             */
/*   Updated: 2025/07/16 20:32:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Safely sets a boolean value with mutex protection.
 * 
 * Locks the provided mutex, updates the target boolean variable, and then
 * unlocks the mutex. Ensures thread-safe modification of shared boolean flags.
 * 
 * @param mutex Pointer to the mutex protecting the boolean variable.
 * @param dest Pointer to the boolean variable to modify.
 * @param value New boolean value to assign.
 * 
 * @note Typically used to set flags such as `end_simulation`, `philo->full`,
 * or `all_threads_ready` in a thread-safe manner.
 * 
 * @see get_bool(), safe_mutex_handle()
 */
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Safely reads a boolean value with mutex protection.
 * 
 * Locks the given mutex, reads the target boolean variable, and unlocks 
 * the mutex.
 * Guarantees thread-safe access to shared boolean flags in the simulation.
 * 
 * @param mutex Pointer to the mutex protecting the boolean variable.
 * @param value Pointer to the boolean variable to read.
 * @return The value of the boolean variable at the time of access.
 * 
 * @note Commonly used to read flags such as `end_simulation`, `full`, or 
 * `all_threads_ready` from shared state.
 * 
 * @see set_bool(), safe_mutex_handle()
 */
bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Safely writes a long integer value with mutex protection.
 * 
 * Locks the provided mutex, updates the target long variable with the new value,
 * and then unlocks the mutex. Ensures thread-safe write access to shared data.
 * 
 * @param mutex Pointer to the mutex protecting the value.
 * @param dest Pointer to the long variable to modify.
 * @param value New value to assign to the target variable.
 * 
 * @note Typically used to update `last_meal_time` or shared counters 
 * between threads.
 * 
 * @see safe_mutex_handle(), get_long()
 */
void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Safely reads a long integer value with mutex protection.
 * 
 * Locks the provided mutex, reads the value, and then unlocks the mutex.
 * This ensures thread-safe access to shared long variables in the simulation.
 * 
 * @param mutex Pointer to the mutex protecting the value.
 * @param value Pointer to the long integer variable to read.
 * @return The value of the long integer at the moment of access.
 * 
 * @note This function is commonly used to safely read timestamps such as
 * `last_meal_time` or other shared counters between threads.
 * 
 * @see safe_mutex_handle()
 */
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Checks whether the philosopher simulation should stop.
 * 
 * Reads the `end_simulation` flag from the table in a thread-safe way,
 * using a mutex-protected access. This function is typically called by
 * philosopher threads and the monitor thread to determine if execution
 * should terminate.
 * 
 * @param table Pointer to the main simulation table.
 * @return true if the simulation is marked as finished, false otherwise.
 * 
 * @see get_bool()
 */
bool	simulation_finish(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
