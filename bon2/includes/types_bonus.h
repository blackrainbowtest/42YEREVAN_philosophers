/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:18:39 by root              #+#    #+#             */
/*   Updated: 2025/07/22 23:45:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <semaphore.h>
# include <stdbool.h>

struct s_table;

// semaphores
typedef struct s_sem
{
	//"/die_sem"
	sem_t	*die_sem;
	//"/fork_sem"
	sem_t	*fork_sem;
	//"/meal_sem"
	sem_t	*meal_sem;
	//"/write_sem"
	sem_t	*write_sem;
	//"/sync_sem"
	sem_t	*sync_sem;
}	t_sem;

// time counters
typedef struct s_time
{
	//time_to_die
	long	time_to_die;
	//time_to_eat
	long	time_to_eat;
	//time_to_sleep;
	long	time_to_sleep;
	//time_to_start;
	long	time_to_start;
}	t_time;

// philo
typedef struct s_philo
{
	long			id;
	long			meals_eaten;
	long			time_born;
	long			time_last_meal;
	bool			full;
	struct s_table	*table;
}	t_philo;

// table
typedef struct s_table
{
	long			philo_count;
	long			meals_limit;
	t_philo			**philos;
	t_time			*time;
	t_sem			*sem;
	pid_t			*pid;
	bool			end_simulation;
}	t_table;

#endif	/* TYPES_BONUS_H */