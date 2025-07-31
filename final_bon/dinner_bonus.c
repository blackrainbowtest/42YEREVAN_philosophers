/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:21:36 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/31 19:21:36 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*dead_checker_routine(void *arg)//NO LEAK HERE
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		safe_sem_handle(&philo->table->sem->die_sem, WAIT);
		if (get_time(philo->table, MICROSECOND) - philo->time_last_meal
			> philo->table->time->time_to_die)
		{
			write_status(DIED, philo, DEBUG_MODE, true);
			sem_post(philo->table->sem->end_sem);
			break ;
		}
		safe_sem_handle(&philo->table->sem->die_sem, POST);
	}
	return (NULL);
}

static void	*meal_checker_routine(void *arg)
{
	t_table	*table;
	long	full_count;

	table = (t_table *)arg;
	full_count = 0;
	while (true)
	{
		safe_sem_handle(&table->sem->meal_sem, WAIT);
		++full_count;
		if (full_count >= table->philo_count)
			safe_sem_handle(&table->sem->end_sem, POST);
	}
	return (NULL);
}

static void	philo_routine(t_philo *philo)
{
	while (true)
	{
		safe_sem_handle(&philo->table->sem->sem_eat_slots, WAIT);
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		safe_sem_handle(&philo->table->sem->sem_eat_slots, POST);
		philo_sleep(philo);
		if (philo->table->philo_count % 2 != 0)
			philo_think(philo);
	}
}

static void	run_simulation(t_table *table, long index)
{
	pthread_t	dead_checker;
	t_philo		*philo;

	philo = table->philos[index];
	philo->time_born = get_time(table, MILLISECOND);
	philo->time_last_meal = get_time(table, MICROSECOND);
	if (pthread_create(&dead_checker, NULL, dead_checker_routine, philo) != 0)
		clean_exit(table, C"pthread_create"RED" failed\n"RST, EXIT_FAILURE);
	if (pthread_detach(dead_checker) != 0)
		clean_exit(table, C"pthread_detach"RED" failed\n"RST, EXIT_FAILURE);
	philo_routine(philo);
	safe_sem_handle(&table->sem->end_sem, POST);
	exit(EXIT_SUCCESS);
}

void	dinner_start(t_table *table)
{
	long		i;
	long		count;
	pthread_t	meal_checker;

	count = table->philo_count;
	if (table->meals_limit > 0)
	{
		if (pthread_create(&meal_checker, NULL,
				meal_checker_routine, table) != 0)
			clean_exit(table, C"pthread_create"RED" failed\n"RST, EXIT_FAILURE);
		if (pthread_detach(meal_checker) != 0)
			clean_exit(table, C"pthread_detach"RED" failed\n"RST, EXIT_FAILURE);
	}
	i = -1;
	while (++i < count)
	{
		table->pid[i] = fork();
		if (table->pid[i] < 0)
			clean_exit(table, C"Fork"RED" failed\n"RST, EXIT_FAILURE);
		if (table->pid[i] == 0)
			run_simulation(table, i);
	}
	sem_wait(table->sem->end_sem);
	set_bool(&table->sem->sync_sem, &table->end_simulation, true);
	i = -1;
	while (++i < count)
		kill(table->pid[i], SIGKILL);
	i = -1;
	while (++i < count)
		waitpid(table->pid[i], NULL, 0);
}
