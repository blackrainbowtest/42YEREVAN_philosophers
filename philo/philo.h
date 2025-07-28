/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:50:17 by root              #+#    #+#             */
/*   Updated: 2025/07/27 21:42:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define MAX_PHILOS 200
# define NONE -1

struct					s_table;
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	long			id;
	long			meals_eaten;
	long			first_fork;
	long			second_fork;
	long long		last_meal_time;
	struct s_table	*table;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_table
{
	long			philo_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_count;
	long long		start_time;
	bool			someone_died;
	bool			all_philos_ate;
	t_mutex			mtx_meal_check;
	t_mutex			mtx_print;
	t_mutex			mtx_forks[MAX_PHILOS];
	t_philo			philos[MAX_PHILOS];
}	t_table;

/**
 * FILES
 */
/*===========init.c=================*/
int		ft_init(t_table *table, char **argv);
/*===========utils_text.c==============*/
long	ft_atol(const char *p_str);
/*===========utils_exit.c==============*/
int		write_error(const char *msg);
int		error_manager(int error_code);
/**
 * DEFINITIONS
 */
typedef enum e_exit
{
	EXIT_THREAD = 2,
	EXIT_INVALID_ARG,
	EXIT_MALLOC_FAIL,
	EXIT_MUTEX,
	EXIT_TABLE_INIT,
	EXIT_PHILO_INIT,
}	t_exit;
#endif