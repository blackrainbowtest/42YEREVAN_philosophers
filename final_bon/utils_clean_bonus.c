/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clean_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:32:08 by root              #+#    #+#             */
/*   Updated: 2025/07/22 00:32:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_semaphores(void)
{
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_SYNC);
	sem_unlink(EAT_SLOTS_SYNC);
}

static void	close_semaphores(t_sem *sem)
{
	if (sem->die_sem)
		sem_close(sem->die_sem);
	if (sem->end_sem)
		sem_close(sem->end_sem);
	if (sem->fork_sem)
		sem_close(sem->fork_sem);
	if (sem->meal_sem)
		sem_close(sem->meal_sem);
	if (sem->write_sem)
		sem_close(sem->write_sem);
	if (sem->sync_sem)
		sem_close(sem->sync_sem);
	if (sem->sem_eat_slots)
		sem_close(sem->sem_eat_slots);
}

void	error_exit(const char *error)
{
	int	len;

	len = 0;
	while (error[len])
		len++;
	write(2, "Error:", 7);
	write(2, error, len);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

static void	free_table(t_table *table)
{
	if (!table)
		return;
	if (table->philos)
		free(table->philos);
	if (table->time)
		free(table->time);
	if (table->sem)
		free(table->sem);
	if (table->pid)
		free(table->pid);
}

void	clean_exit(t_table *table, const char *msg,
		bool is_parent, int exit_code)
{
	long	i;

	if (!table)
		exit(exit_code);
	// if (is_parent && table->pid)
	// {
	// 	i = -1;
	// 	while (++i < table->philo_count)
	// 	{
	// 		if (table->pid && table->pid[i] > 0)
	// 			kill(table->pid[i], SIGKILL);
	// 	}
	// }
	if (table->philos)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			if (table->philos && table->philos[i])
				free(table->philos[i]);
		}
	}
	cleanup_semaphores();// OK NO LEAK NO ZOMBIE
	close_semaphores(table->sem);// OK NO LEAK NO ZOMBIE
	free_table(table);// OK NO LEAK NO ZOMBIE
	if (msg)
		printf(RED"%s\n"RST, msg);
	exit(exit_code);
}
