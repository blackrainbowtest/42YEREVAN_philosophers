/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:54:01 by aramarak          #+#    #+#             */
/*   Updated: 2025/07/20 16:57:32 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <semaphore.h>

struct s_table;

typedef struct s_philo
{
	pid_t				pid;
	int					id;
	long				last_meal_time;
	long				meals_counter;
	bool				full;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				number_of_limit_meals;

	long				start_time;
	bool				end_simulation;
	bool				all_processes_ready;
	pid_t				*pids;

	sem_t				*forks;
	sem_t				*sync_lock;
	sem_t				*write_lock;
	sem_t				*meal_check;
	sem_t				*finish;
	sem_t				*ready_count;

	t_philo				*philos;
}	t_table;

#endif