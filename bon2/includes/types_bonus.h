/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:18:39 by root              #+#    #+#             */
/*   Updated: 2025/07/20 23:46:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <semaphore.h>

struct s_table;

// semaphores
typedef struct s_sem
{
	//"/die_sem"
	sem_t	*die_sem;
	//"/fork_sem"
	sem_t	*form_sem;
	//"/meal_sem"
	sem_t	*meal_sem;
	//"/write_sem"
	sem_t	*write_sem;
}	t_sem;

// time counters
typedef struct s_time
{
	//time_to_die
	long	time_to_die;
	//time_to_eat
	long	time_to_sleep;
	//time_to_sleep;
	long	time_to_sleep;
	//time_last_meal;
	long	time_last_meal;
	//time_to_start;
	long	time_to_start;
}	t_time;

// philo
typedef struct s_philo
{
	long			id;
	long			meals_eaten;
	t_time			*time;
	t_sem			*sem;
	struct s_table	*table;
}	t_philo;

// table
typedef struct s_table
{
	long			philo_count;
	long			meals_limit;
	t_philo			**philo;
	t_time			*time;
	t_sem			*sem;
}	t_table;

#endif	/* TYPES_BONUS_H */