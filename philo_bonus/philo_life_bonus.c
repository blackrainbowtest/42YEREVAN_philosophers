/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:49:53 by root              #+#    #+#             */
/*   Updated: 2025/08/05 19:08:22 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	long	now;

	philo = (t_philo *)arg;
	table = philo->table;
	while (true)
	{
		sem_wait(table->meal_check);
		now = get_time_ms();
		if (now - philo->last_meal_time > table->time_to_die)
		{
			print_action(philo, "died");
			sem_post(table->finish);
			sem_post(table->meal_check);
			exit(EXIT_SUCCESS);
		}
		sem_post(table->meal_check);
		usleep(1000);
	}
	return (NULL);
}

void	print_action(t_philo *philo, char *msg)
{
	long	time;

	sem_wait(philo->table->write_lock);
	time = get_time_ms() - philo->table->start_time;
	printf("%ld %d %s\n", time, philo->id, msg);
	sem_post(philo->table->write_lock);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->table->forks);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(table->meal_check);
	philo->last_meal_time = get_time_ms();
	sem_post(table->meal_check);
	print_action(philo, "is eating");
	usleep((table->time_to_eat * 1000));
	philo->meals_eaten++;
}

void	sleep_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_action(philo, "is thinking");
}
