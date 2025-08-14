/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:56:13 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/14 19:47:46 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_death(t_table *table, int i)
{
	long long	last_meal;
	bool		died;

	pthread_mutex_lock(&(table->mtx_meal_check));
	last_meal = table->philos[i].last_meal_time;
	pthread_mutex_unlock(&(table->mtx_meal_check));
	if (ft_time_from_last_meal(last_meal, get_time()) > table->time_to_die)
	{
		write_message(table, i, "died");
		pthread_mutex_lock(&(table->mtx_death));
		table->someone_died = true;
		pthread_mutex_unlock(&(table->mtx_death));
		return (true);
	}
	pthread_mutex_lock(&(table->mtx_death));
	died = table->someone_died;
	pthread_mutex_unlock(&(table->mtx_death));
	return (died);
}

static void	check_meals(t_table *table)
{
	int	i;

	if (table->meals_count == -1)
		return ;
	pthread_mutex_lock(&(table->mtx_meal_check));
	i = 0;
	while (i < table->philo_count
		&& table->philos[i].meals_eaten >= table->meals_count)
		i++;
	if (i == table->philo_count)
		table->all_philos_ate = true;
	pthread_mutex_unlock(&(table->mtx_meal_check));
}

static void	monitor_loop(t_table *table)
{
	int		i;
	bool	dead;

	pthread_mutex_lock(&(table->mtx_meal_check));
	dead = table->someone_died;
	pthread_mutex_unlock(&(table->mtx_meal_check));
	while (!table->all_philos_ate)
	{
		i = -1;
		while (++i < table->philo_count && !dead)
		{
			if (check_death(table, i))
				break ;
			usleep(100);
		}
		pthread_mutex_lock(&(table->mtx_meal_check));
		dead = table->someone_died;
		pthread_mutex_unlock(&(table->mtx_meal_check));
		if (dead)
			break ;
		check_meals(table);
	}
}

void	ft_monitor(t_table *table)
{
	monitor_loop(table);
}
