/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:51:21 by root              #+#    #+#             */
/*   Updated: 2025/08/03 16:16:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	parse_input(int argc, char **argv, t_table *table)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (false);
	i = 0;
	while (argv[++i])
	{
		if (!is_digit_str(argv[i]))
			return (false);
	}
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->must_eat_count = -1;
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	if (table->philo_count <= 0 || table->philo_count > MAX_PHILOS
		|| table->time_to_die < MIN_TIME || table->time_to_die > MAX_TIME
		|| table->time_to_eat < MIN_TIME || table->time_to_sleep < MIN_TIME)
		return (false);
	if (table->must_eat_count == 0)
		return (false);
	return (true);
}

bool	init_table(t_table *table)
{
	table->start_time = get_time_ms();
	table->all_alive = true;
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (false);
	return (true);
}

bool	init_semaphores(t_table *table)
{
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_WRITE_NAME);
	sem_unlink(SEM_MEAL_NAME);
	sem_unlink(SEM_FINISH_NAME);
	table->forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0644, table->philo_count);
	table->write_lock = sem_open(SEM_WRITE_NAME, O_CREAT, 0644, 1);
	table->meal_check = sem_open(SEM_MEAL_NAME, O_CREAT, 0644, 1);
	table->finish = sem_open(SEM_FINISH_NAME, O_CREAT, 0644, 0);
	if (table->forks == SEM_FAILED || table->write_lock == SEM_FAILED
		|| table->meal_check == SEM_FAILED || table->finish == SEM_FAILED)
	{
		printf(RED "Error: " RST "Failed to open one or more semaphores.\n");
		return (false);
	}
	return (true);
}

bool	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].pid = -1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].table = table;
		i++;
	}
	return (true);
}
