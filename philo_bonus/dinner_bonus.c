/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:53 by root              #+#    #+#             */
/*   Updated: 2025/07/19 22:12:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	dinner_start(t_table *table)
{
	int		i;
	pid_t	pid;

	i = -1;
	if (0 == table->number_of_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		;
	else
	{
		table->start_time = gettime(MILLISECOND);
		while (++i < table->philo_nbr)
		{
			pid = fork();
			if (pid < 0)
				error_exit("fork() failed");
			else if (0 == pid)
			{
				philo_routine(&table->philos[i]); //TODO
				exit(0);
			}
			table->philos[i].pid = pid;
			usleep(100);
		}
	}
}