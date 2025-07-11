/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:26:55 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/11 19:29:52 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * [time_ms] [philo_id] [action]
 * 
 * thread safe
 * timestamp_in_ms [philosopher_number] action nl
 */

void	write_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILISECOND);
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finish(philo->table))
			printf(W"%-6ld"RST"\t[%d]\ttake a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"C"\t[%d]\teating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_finish(philo->table))
			printf(W"%-6ld"RST"\t[%d]\tis sleeping\n", elapsed, philo->id);
		else if (THINKING == status)
			printf(W"%-6ld"RST"\t[%d]\tthinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(W"%-6ld\t[%d]\tdied"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
