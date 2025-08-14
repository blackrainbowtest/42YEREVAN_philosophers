/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:56:37 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/14 19:26:46 by aramarak         ###   ########.fr       */
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
	t_mutex			mtx_death;
	t_mutex			mtx_forks[MAX_PHILOS];
	t_philo			philos[MAX_PHILOS];
}	t_table;

/**
 * FILES
 */

/*===========init.c=================*/
int			ft_init(t_table *table, char **argv);

/*===========utils_text.c==============*/
long		ft_atol(const char *p_str);
void		write_message(t_table *table, long id, char *msg);

/*===========utils_exit.c==============*/
int			write_error(const char *msg);
int			error_manager(int error_code);

/*===========utils_time.c==============*/
long long	get_time(void);
long long	ft_time_from_last_meal(long long past, long long pres);
void		smart_sleep(long long time, t_table *table);
void		precise_usleep(long usec);

/*===========simulate.c==============*/
int			ft_simulate(t_table *table);
void		*ft_thread(void *arg);
void		ft_end_simulation(t_table *table);

/*===========simulate.c==============*/
void		ft_monitor(t_table *table);
/**
 * DEFINITIONS
 */
typedef enum e_exit
{
	EXIT_THREAD_ERROR = 2,
	EXIT_INVALID_ARG,
	EXIT_MALLOC_FAIL,
	EXIT_MUTEX,
	EXIT_TABLE_INIT,
	EXIT_PHILO_INIT,
	EXIT_INT_ERROR,
	EXIT_INPUT_ERROR,
	EXIT_EMPTY_ERROR,
	EXIT_NEGATIVE_ERROR,
	EXIT_ZERO_ERROR,
	EXIT_MINIMUM_ERROR,
	EXIT_UNKNOWN_ERROR,
}	t_exit;

# define INT_ERROR "The value is too big, INT_MAX is the limit."
# define THREAD_ERROR "There was an error creating the threads."
# define INPUT_ERROR "Incorrect input! Use only digits."
# define EMPTY_ERROR "Input is empty or only spaces."
# define NEGATIVE_ERROR "Can't handle negative numbers! Use positive ones."
# define INVALID_ARG "A least one invalid argument."
# define MALLOC_FAIL "Failed to allocate memory for table."
# define MUTEX_ERROR "Fatal error when intializing mutex."
# define ZERO_ERROR "Cant use zero count. Use positive number."
# define MINIMUM_ERROR "Need use bigger value."
# define UNKNOWN_ERROR "Unknown error type. Please check your input."

#endif /* PHILO_H */
