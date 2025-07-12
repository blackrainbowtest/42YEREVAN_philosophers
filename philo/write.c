/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:26:55 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/13 00:29:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
 * time_ms philo_id action
 * 
 * thread safe
 * timestamp_in_ms philosopher_number action nl
 */

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILISECOND) - philo->table->start_simulation;
	if (philo->full)	// thread safe
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
