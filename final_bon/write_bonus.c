/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:39:45 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/31 19:39:45 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	write_status_debug(t_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FORK == status)
		printf(W"%ld"RST" %ld has taken the fork"
			"   NO:"B"%d\n"RST, elapsed, philo->id,
			42);
	else if (EATING == status)
		printf(W"%ld"C" %ld is eating"
			"   "Y"%ld\n"RST, elapsed, philo->id, philo-> meals_eaten);
	else if (SLEEPING == status)
		printf(W"%ld"C" %ld is sleeping\n"RST, elapsed, philo->id);
	else if (THINKING == status)
		printf(W"%ld"C" %ld is thinking\n"RST, elapsed, philo->id);
	else if (DIED == status)
		printf(RED"%ld %ld is died\n"RST, elapsed, philo->id);
}

void	write_status(t_status status, t_philo *philo, bool debug, bool is_end)
{
	long	elapsed;

	elapsed = get_time(philo->table, MILLISECOND) - philo->time_born;
	if (philo->full)
		return ;
	safe_sem_handle(&philo->table->sem->write_sem, WAIT);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if (TAKE_FORK == status)
			printf(W"%-ld"RST" %ld has taken a fork\n", elapsed, philo->id);
		else if (DROP_FORK == status)
			printf(C"%-ld"RST" %ld has drop a fork\n", elapsed, philo->id);
		else if (EATING == status)
			printf(W"%-ld"C" %ld is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status)
			printf(W"%-ld"RST" %ld is sleeping\n", elapsed, philo->id);
		else if (THINKING == status)
			printf(W"%-ld"RST" %ld is thinking\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-ld %ld died\n"RST, elapsed, philo->id);
	}
	if (!is_end)
		safe_sem_handle(&philo->table->sem->write_sem, POST);
}
