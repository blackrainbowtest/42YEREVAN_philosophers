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
	return (sem->die_sem == SEM_FAILED || sem->fork_sem == SEM_FAILED
		|| sem->meal_sem == SEM_FAILED || sem->write_sem == SEM_FAILED);
}

static inline bool	any_semaphore_failed_to_unlink(void)
{
	return (sem_unlink(SEM_DIE) == -1 || sem_unlink(SEM_FORK) == -1
		|| sem_unlink(SEM_MEAL) == -1 || sem_unlink(SEM_WRITE) == -1);
}

static void	init_philosophers(t_table *p_table)
{
	t_philo	**p_philos;
	long	i;
	long	now;

	p_philos = (t_philo **)safe_malloc(sizeof(t_philo *)
			* p_table->philo_count);
	now = get_time(p_table, MILLISECOND);
	i = -1;
	while (++i < p_table->philo_count)
	{
		p_philos[i] = (t_philo *)safe_malloc(sizeof(t_philo));
		p_philos[i]->id = i + 1;
		p_philos[i]->table = p_table;
		p_philos[i]->meals_eaten = 0;
		p_philos[i]->time_born = now;
		p_philos[i]->time_last_meal = now;
	}
	p_table->philos = p_philos;
}

static void	init_semaphores(t_table *p_table)
{
	t_sem	*sem;

	cleanup_semaphores();
	sem = (t_sem *)safe_malloc(sizeof(t_sem));
	memset(sem, 0, sizeof(t_sem));
	sem->die_sem = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 1);
	sem->fork_sem = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0644,
			p_table->philo_count);
	sem->meal_sem = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 0);
	sem->write_sem = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	if (any_semaphore_failed_to_open(sem))
		clean_exit(p_table, "Semaphore "RED"OPEN"RST
			" Error\n", true, EXIT_FAILURE);
	if (any_semaphore_failed_to_unlink())
		clean_exit(p_table, "Semaphore "RED"UNLINK"RST
			" Error\n", true, EXIT_FAILURE);
	p_table->sem = sem;
}

void	data_init(t_table *p_table)
{
	init_semaphores(p_table);
	init_philosophers(p_table);
}
