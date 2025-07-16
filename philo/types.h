/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:24:45 by root              #+#    #+#             */
/*   Updated: 2025/07/13 01:27:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

struct s_table;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	struct s_table *table;
}	t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_number;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	monitor;
}	t_table;

#endif