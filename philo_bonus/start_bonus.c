/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:21:35 by root              #+#    #+#             */
/*   Updated: 2025/08/05 19:16:00 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_meals(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	while (i < table->philo_count)
	{
		sem_wait(table->meal_counter);
		i++;
	}
	sem_post(table->finish);
	return (NULL);
}

void	philo_lifecycle(t_philo *philo)
{
	t_table		*table;
	pthread_t	monitor;

	table = philo->table;
	pthread_create(&monitor, NULL, monitor_death, philo);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		take_forks(philo);
		eat(philo);
		sem_post(table->forks);
		sem_post(table->forks);
		if (table->must_eat_count != -1
			&& philo->meals_eaten >= table->must_eat_count)
		{
			sem_post(table->meal_counter);
			break ;
		}
		sleep_think(philo);
	}
	while (1)
		pause();
}

static bool	meal_monitor(t_table *table)
{
	pthread_t	meal_monitor;

	if (table->must_eat_count != -1)
	{
		if (pthread_create(&meal_monitor, NULL, monitor_meals, table) != 0)
		{
			printf(RED "Error: " RST "Failed to create meal monitor thread.\n");
			return (false);
		}
		pthread_detach(meal_monitor);
	}
	return (true);
}

bool	start_simulation(t_table *table)
{
	int			i;
	pid_t		pid;

	i = 0;
	while (i < table->philo_count)
	{
		pid = fork();
		if (pid < 0)
		{
			printf(RED "Error: " RST "Fork failed for philo %d\n", i + 1);
			return (false);
		}
		else if (pid == 0)
		{
			philo_lifecycle(&table->philos[i]);
			exit(EXIT_SUCCESS);
		}
		else
			table->philos[i].pid = pid;
		i++;
	}
	if (!meal_monitor(table))
		return (false);
	return (true);
}

void	dinner_start(t_table *table)
{
	int	i;

	if (!start_simulation(table))
		return ;
	sem_wait(table->finish);
	i = -1;
	while (++i < table->philo_count)
		kill(table->philos[i].pid, SIGTERM);
	i = -1;
	while (++i < table->philo_count)
		waitpid(table->philos[i].pid, NULL, 0);
}
