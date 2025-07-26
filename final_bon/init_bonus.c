/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:31:47 by root              #+#    #+#             */
/*   Updated: 2025/07/22 00:31:47 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline bool	any_semaphore_failed_to_open(t_sem *sem)
{
	return (sem->die_sem == SEM_FAILED || sem->end_sem == SEM_FAILED
		|| sem->fork_sem == SEM_FAILED || sem->meal_sem == SEM_FAILED
		|| sem->write_sem == SEM_FAILED || sem->sync_sem == SEM_FAILED);
}

static inline bool	any_semaphore_failed_to_unlink(void)
{
	return (sem_unlink(SEM_DIE) == -1 || sem_unlink(SEM_END) == -1
		|| sem_unlink(SEM_FORK) == -1 || sem_unlink(SEM_MEAL) == -1
		|| sem_unlink(SEM_WRITE) == -1 || sem_unlink(SEM_SYNC) == -1);
}

static void	init_philosophers(t_table *table)
{
	t_philo	**p_philos;
	long	i;
	long	now;

	p_philos = table->philos;
	now = get_time(table, MILLISECOND);
	i = -1;
	while (++i < table->philo_count)
	{
		p_philos[i] = (t_philo *)safe_malloc(sizeof(t_philo));
		p_philos[i]->id = i + 1;
		p_philos[i]->meals_eaten = 0;
		p_philos[i]->time_born = now;
		p_philos[i]->time_last_meal = now;
		p_philos[i]->full = false;
		p_philos[i]->table = table;
	}
}

static void	init_semaphores(t_table *table)
{
	t_sem	*sem;

	cleanup_semaphores();
	sem = table->sem;
	sem->die_sem = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 0);
	sem->end_sem = sem_open(SEM_END, O_CREAT | O_EXCL, 0644, 0);
	sem->fork_sem = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0644,
			table->philo_count);
	sem->meal_sem = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 0);
	sem->write_sem = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	sem->sync_sem = sem_open(SEM_SYNC, O_CREAT | O_EXCL, 0644, table->philo_count - 1);
	if (any_semaphore_failed_to_open(sem))
		clean_exit(table, "Semaphore "RED"OPEN"RST
			" Error\n", true, EXIT_FAILURE);
	if (any_semaphore_failed_to_unlink())
		clean_exit(table, "Semaphore "RED"UNLINK"RST
			" Error\n", true, EXIT_FAILURE);
}

void	data_init(t_table *table)
{
	init_semaphores(table);
	init_philosophers(table);
}
