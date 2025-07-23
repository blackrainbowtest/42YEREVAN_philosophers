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
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

static void	free_table(t_table *table)
{
	if (table->pid)
		free(table->pid);
	if (table->time)
		free(table->time);
	if (table->sem)
		free(table->sem);
}

void	clean_exit(t_table *table, const char *msg,
		bool is_parent, int exit_code)
{
	long	i;

	if (!table)
		exit(exit_code);
	if (is_parent && table->pid)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			if (table->pid[i] > 0)
				kill(table->pid[i], SIGKILL);
		}
	}
	if (table->philos)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			if (table->philos[i])
				free(table->philos[i]);
		}
		free(table->philos);
	}
	free_table(table);
	if (msg)
		printf(RED"%s\n"RST, msg);
	exit(exit_code);
}
