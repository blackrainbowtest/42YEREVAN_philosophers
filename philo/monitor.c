/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:40:14 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/07 22:50:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_death(t_table *table, int i)
{
	long long	last_meal;

	pthread_mutex_lock(&(table->mtx_meal_check));
	last_meal = table->philos[i].last_meal_time;
	if (ft_time_from_last_meal(last_meal, get_time()) > table->time_to_die)
	{
		write_message(table, i, "died");
		table->someone_died = true;
	}
	pthread_mutex_unlock(&(table->mtx_meal_check));
	return (table->someone_died);
}

static void	check_meals(t_table *table)
{
	int	i;

	if (table->meals_count == -1)
		return ;
	i = 0;
	while (i < table->philo_count
		&& table->philos[i].meals_eaten >= table->meals_count)
		i++;
	if (i == table->philo_count)
		table->all_philos_ate = true;
}

static void	monitor_loop(t_table *table)
{
	int	i;

	while (!table->all_philos_ate)
	{
		i = -1;
		while (++i < table->philo_count && !table->someone_died)
		{
			if (check_death(table, i))
				break ;
			usleep(100);
		}
		if (table->someone_died)
			break ;
		check_meals(table);
	}
}

void	ft_monitor(t_table *table)
{
	monitor_loop(table);
}
