/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:04:53 by root              #+#    #+#             */
/*   Updated: 2025/07/24 16:37:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_BONUS_H
# define DEFS_BONUS_H

/*====SEMAPHORE NAMES====*/
# define SEM_DIE	"/die_sem"
# define SEM_END	"/end_sem"
# define SEM_FORK	"/fork_sem"
# define SEM_MEAL	"/meal_sem"
# define SEM_WRITE	"/write_sem"
# define SEM_SYNC	"/sync_sem"

/*====PHILO LIMITS====*/
# define MAX_PHILO_COUNT 200

/*====MIN MEAL TIME====*/
# define MEAL_MIN 60

/*====COLORS====*/
# define RST "\033[0m"
# define RED "\033[1;31m"
# define G   "\033[1;32m"
# define Y   "\033[1;33m"
# define B   "\033[1;34m"
# define M   "\033[1;35m"
# define C   "\033[1;36m"
# define W   "\033[1;37m"

/*====DEBUG====*/
# define DEBUG_MODE 0

/*====MONITOR COUNT====*/
#define MONITOR_COUNT 2

/*====WRITE ACTIONS====*/
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK,
	DROP_FORK,
	DIED,
}	t_status;

/*====TIME TYPES====*/
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_opcode
{
	WAIT,
	POST,
	CLOSE,
	CREATE,
}	t_opcode;

#endif	/* DEFS_BONUS_H */