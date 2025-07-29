/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:53:15 by root              #+#    #+#             */
/*   Updated: 2025/07/29 20:41:48 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_end_simulation(t_table *table)
{
	long			i;
	t_philo			*philos;

	philos = table->philos;
	i = -1;
	while (++i < table->philo_count)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&(table->mtx_forks[i]));
	pthread_mutex_destroy(&(table->mtx_print));
}

static void	meal_simulation(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&(table->mtx_forks[philo->first_fork]));
	write_message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->mtx_forks[philo->second_fork]));
	write_message(table, philo->id, "has taken a fork");
	pthread_mutex_lock(&(table->mtx_meal_check));
	write_message(table, philo->id, "is eating");
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&(table->mtx_meal_check));
	smart_sleep(table->time_to_eat, table);
	(philo->meals_eaten)++;
	pthread_mutex_unlock(&(table->mtx_forks[philo->first_fork]));
	pthread_mutex_unlock(&(table->mtx_forks[philo->second_fork]));
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2)
		usleep(15000);
	while (!(table->someone_died))
	{
		meal_simulation(philo);
		if (table->all_philos_ate)
			break ;
		write_message(table, philo->id, "is sleeping");
		smart_sleep(table->time_to_sleep, table);
		write_message(table, philo->id, "is thinking");
	}
	return (NULL);
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
		philos[i].last_meal_time = get_time();
		if (pthread_create(&philos[i].thread_id, NULL, ft_thread, &(philos[i])))
			return (EXIT_FAILURE);
		++i;
	}
	ft_monitor(table);
	ft_end_simulation(table);
	return (EXIT_SUCCESS);
}
