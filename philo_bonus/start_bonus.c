/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:21:35 by root              #+#    #+#             */
/*   Updated: 2025/08/03 18:12:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_lifecycle(t_philo *philo)
{
	t_table	*table = philo->table;
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitor_death, philo);
	pthread_detach(monitor);
	if (philo->id % 2 == 0)
		usleep(100);

	while (1)
	{
		take_forks(philo);
		eat(philo);
		sem_post(table->forks);
		sem_post(table->forks);
		sleep_think(philo);
	}
}

bool	start_simulation(t_table *table)
{
	int		i;
	pid_t	pid;

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
		{
			table->philos[i].pid = pid;
		}
		i++;
	}
	return (true);
}
