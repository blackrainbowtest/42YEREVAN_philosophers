/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:06:26 by root              #+#    #+#             */
/*   Updated: 2025/07/29 19:48:01 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_init_philos(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].meals_eaten = 0;
		table->philos[i].first_fork = i;
		table->philos[i].second_fork = (i + 1) % table->philo_count;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
	}
	return (EXIT_SUCCESS);
}

static	int	ft_init_mutexses(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_mutex_init(&(table->mtx_forks[i]), NULL))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(table->mtx_meal_check), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(table->mtx_print), NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static	int	ft_init_table(t_table *table, char **argv)
{
	table->philo_count = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->meals_count = -1;
	table->someone_died = false;
	table->all_philos_ate = false;
	if (table->philo_count < 2 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0
		|| table->philo_count > MAX_PHILOS)
		return (EXIT_FAILURE);
	if (argv[5])
	{
		table->meals_count = ft_atol(argv[5]);
		if (table->meals_count <= 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_init(t_table *table, char **argv)
{
	int	exit_code;

	exit_code = ft_init_table(table, argv);
	if (exit_code != EXIT_SUCCESS)
		return (EXIT_TABLE_INIT);
	exit_code = ft_init_mutexses(table);
	if (exit_code != EXIT_SUCCESS)
		return (EXIT_MUTEX);
	exit_code = ft_init_philos(table);
	if (exit_code != EXIT_SUCCESS)
		return (EXIT_PHILO_INIT);
	return (EXIT_SUCCESS);
}
