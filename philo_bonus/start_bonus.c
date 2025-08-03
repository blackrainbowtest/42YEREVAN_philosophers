/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:21:35 by root              #+#    #+#             */
/*   Updated: 2025/08/03 17:36:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_lifecycle(t_philo *philo);

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
