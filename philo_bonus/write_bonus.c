/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:39:58 by root              #+#    #+#             */
/*   Updated: 2025/07/19 23:34:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FORK == status && !simulation_finish(philo->table))
		printf(W"%6ld"RST" %d has taken the fork"
			"   NO:"B"%d\n"RST, elapsed, philo->id,
			42);
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

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_time;
	if (philo->full)
		return ;
	safe_sem_handle(&philo->table->write_lock, WAIT);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if (TAKE_FORK == status && !simulation_finish(philo->table))
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
	safe_sem_handle(&philo->table->write_lock, POST);
}
