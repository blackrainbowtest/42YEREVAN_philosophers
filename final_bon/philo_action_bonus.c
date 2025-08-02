/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:43:20 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/31 19:43:20 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->fork_sem, WAIT);
	if (philo->table->philo_count == 1)
		return ;
	safe_sem_handle(&philo->table->sem->fork_sem, WAIT);
}

void	philo_eat(t_philo *philo)
{
	long	time_to_eat;

	if (philo->table->philo_count == 1)
		return ;
	time_to_eat = philo->table->time->time_to_eat;
	philo->time_last_meal = get_time(philo->table, MICROSECOND);
	write_status(EATING, philo, DEBUG_MODE, false);
	precise_usleep(time_to_eat, philo);
	philo->meals_eaten++;
	if (!philo->full && philo->table->meals_limit > 0
		&& philo->meals_eaten >= philo->table->meals_limit)
	{
		philo->full = true;
		safe_sem_handle(&philo->table->sem->meal_sem, POST);
	}
}

void	drop_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->fork_sem, POST);
	if (philo->table->philo_count == 1)
		return ;
	safe_sem_handle(&philo->table->sem->fork_sem, POST);
}

void	philo_sleep(t_philo *philo)
{
	long	time_to_sleep;

	time_to_sleep = philo->table->time->time_to_sleep;
	if (philo->table->philo_count != 1)
		write_status(SLEEPING, philo, DEBUG_MODE, false);
	precise_usleep(time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (philo->full || philo->table->philo_count == 1)
		return ;
	write_status(THINKING, philo, DEBUG_MODE, false);
	t_eat = philo->table->time->time_to_eat;
	t_sleep = philo->table->time->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo);
}
