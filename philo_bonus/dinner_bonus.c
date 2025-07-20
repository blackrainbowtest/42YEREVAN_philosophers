/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:53 by root              #+#    #+#             */
/*   Updated: 2025/07/20 13:23:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void philo_routine(t_philo *philo)
{
    // philo->last_meal_time = gettime(MILLISECOND);

    while (!simulation_finish(philo->table))
    {
        // здесь вызовы с семафорами внутри
        // take_forks(philo);
        // start_eating(philo);
        // finish_eating(philo);
        // start_sleeping(philo);
        // start_thinking(philo);
    }
	write_status(EATING, philo, true);
	exit(0);
    // cleanup_and_exit(philo);
}

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
	table->start_time = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
}