/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:53:15 by root              #+#    #+#             */
/*   Updated: 2025/07/28 00:29:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**https://github.com/Gaspachow/philosophers-42 */
#include "philo.h"

long long	ft_time_from_last_meal(long long past, long long pres)
{
	return (pres - past);
}

static void	ft_monitor(t_table *table)
{
	long			i;

	while (!(table->all_philos_ate))
	{
		i = -1;
		while (++i < table->philo_count && !(table->someone_died))
		{
			pthread_mutex_lock(&(table->mtx_meal_check));
			if (ft_time_from_last_meal(table->philos[i].last_meal_time, get_time()) > table->time_to_die)
			{
				write_message(table, i, "died");
				table->someone_died = true;
			}
			pthread_mutex_unlock(&(table->mtx_meal_check));
			usleep(100);
		}
		if (table->someone_died)
			break;
		i = 0;
		while (table->meals_count != -1 && i < table.philo_count
				&& table->meals_count <= table->philos[i].meals_eaten)
			++i;
		if (i >= table->philo_count)
			table->all_philos_ate = true;
	}
}

static void	ft_end_simulation(t_table *table)
{
	long			i;
	t_philo			*philos;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&(table->mtx_forks[i]));
	pthread_mutex_destroy(&(table->mtx_print));
}

static void	*ft_thread(t_philo *philo)
{
	
}

int	ft_simulate(t_table *table)
{
	long	i;
	t_philo	*philos;

	i = 0;
	philos = table->philos;
	table->start_time = get_time();
	while (i < table->philo_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, ft_thread, &(philos[i])))
			return (EXIT_FAILURE);
		philos[i].last_meal_time = get_time();
		++i;
	}
	ft_monitor(table);
	ft_end_simulation(table);
	return (EXIT_SUCCESS);
}