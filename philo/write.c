/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:26:55 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/16 20:22:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Prints detailed, color-coded debug information about philosopher 
 * actions.
 * 
 * Outputs the current state of a philosopher (taking forks, eating, sleeping, 
 * thinking, died) with timestamps, fork numbers, and meal counters, all 
 * formatted with ANSI colors for clarity.
 * 
 * This function is used for debugging and is typically enabled via a debug flag
 * or macro.
 * 
 * @param status Current status of the philosopher (e.g., EATING, SLEEPING, etc)
 * @param philo Pointer to the philosopher structure performing the action.
 * @param elapsed Time elapsed since simulation start, in milliseconds.
 * 
 * @note This function skips printing if the simulation has already finished, 
 * except when reporting DIED.
 * 
 * @see simulation_finish(), t_status
 */
static void	write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finish(philo->table))
		printf(W"%6ld"RST" %d has taken the 1 fork"
			"   NO:"B"%d\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !simulation_finish(philo->table))
		printf(W"%6ld"RST" %d has taken the 2 fork"
			"   NO:"B"%d\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finish(philo->table))
		printf(W"%6ld"C" %d is eating"
			"   "Y"%ld\n"RST, elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !simulation_finish(philo->table))
		printf(W"%6ld"C" %d is sleeping\n"RST, elapsed, philo->id);
	else if (THINKING == status && !simulation_finish(philo->table))
		printf(W"%6ld"C" %d is thinking\n"RST, elapsed, philo->id);
	else if (DIED == status)
		printf(RED"%6ld %d is died\n"RST, elapsed, philo->id);
}

/**
 * @brief Thread-safe printing of philosopher's status to the console.
 * 
 * Prints the current action of a philosopher with timestamp, synchronized
 * using a mutex to prevent interleaved outputs. Supports both normal and
 * debug modes:
 * 
 * - In debug mode, shows detailed information (fork number, meal count, etc.).
 * - In normal mode, prints simple human-readable status messages.
 * 
 * The function checks whether the simulation has ended or the philosopher is 
 * full before printing, except in the case of a DIED status.
 * 
 * @param status The current status of the philosopher (EATING, SLEEPING, etc.).
 * @param philo Pointer to the philosopher struct.
 * @param debug If true, enables extended debug output.
 * 
 * @note Uses `write_mutex` to serialize access to the console.
 * 
 * @see write_status_debug(), safe_mutex_handle(), simulation_finish()
 */
void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finish(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status)
			printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
