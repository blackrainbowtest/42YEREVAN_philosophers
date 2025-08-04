/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:49:53 by root              #+#    #+#             */
/*   Updated: 2025/08/04 23:15:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_table	*table = philo->table;

	while (1)
	{
		sem_wait(table->meal_check);
		long	now = get_time_ms();
		if (now - philo->last_meal_time > table->time_to_die)
		{
			print_action(philo, "died");
			sem_post(table->finish); // сигнал остальным процессам
			sem_post(table->meal_check);
			sem_wait(philo->table->write_lock);
			exit(EXIT_SUCCESS); // философ умер — завершаем процесс
		}
		sem_post(table->meal_check);
		usleep(1000); // проверять раз в 1 мс
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
	t_table	*table = philo->table;

	sem_wait(table->meal_check);
	philo->last_meal_time = get_time_ms();
	sem_post(table->meal_check);
	print_action(philo, "is eating");
	usleep((table->time_to_eat * 1000)); //620
	philo->meals_eaten++;
}

void	sleep_think(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_action(philo, "is thinking");
}
