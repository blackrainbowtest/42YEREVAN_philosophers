/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:32:04 by root              #+#    #+#             */
/*   Updated: 2025/07/22 00:32:04 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	table_time_init(t_table *table, char **argv)
{
	table->time->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time->time_to_die < 6e4
		|| table->time->time_to_eat < 6e4
		|| table->time->time_to_sleep < 6e4)
		error_exit("Time to die, eat or sleep must be more than 60ms.");
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_count = ft_atol(argv[1]);
	table->meals_limit = -1;
	if (argv[5])
		table->meals_limit = ft_atol(argv[5]);
	table->philos = (t_philo **)safe_malloc(sizeof(t_philo *)
			* table->philo_count);
	table->time = (t_time *)safe_malloc(sizeof(t_time));
	table->sem = (t_sem *)safe_malloc(sizeof(t_sem));
	table->pid = (pid_t *)safe_malloc(sizeof(pid_t) * table->philo_count);
	table->end_simulation = false;
	table_time_init(table, argv);
}
