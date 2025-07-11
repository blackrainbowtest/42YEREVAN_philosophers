/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:24:45 by root              #+#    #+#             */
/*   Updated: 2025/07/11 18:50:49 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		// printf
#include <stdlib.h>		// malloc, free
#include <unistd.h>		// usleep
#include <stdbool.h>	// bool
#include <pthread.h>	// mutex: init, lock, unlock, destroy
						// thread: create, join, detach
#include <sys/time.h>	// gettimeofday
#include <limits.h>		// INT_MAX
#include <errno.h>

// ANSI escape sequences for bold colored text
#define RST "\033[0m"      // Reset
#define RED "\033[1;31m"   // Bold Red
#define G   "\033[1;32m"   // Bold Green
#define Y   "\033[1;33m"   // Bold Yellow
#define B   "\033[1;34m"   // Bold Blue
#define M   "\033[1;35m"   // Bold Magenta
#define C   "\033[1;36m"   // Bold Cyan
#define W   "\033[1;37m"   // Bold White
/**
 * OPCODE for mutex
 */
typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,	// denug
	TAKE_SECOND_FORK,	// debug
	DIED,
}		t_status;
 
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

/**
 * CODES FOR GETTIME
 */
typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}			t_time_code;

/** structures */

/**
 * core more redable names
 */
typedef pthread_mutex_t	t_mtx;
typedef struct s_table t_table;

/*
  * Forks
  */
typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;

}				t_fork;
/*
  * philosopher: a struct representing a philosopher
  * ./philo 5 800 200 200 [5]
  */
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time; // time passed from the meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;		// a philo is a thread
	t_table		*table;
}				t_philo;

/**
 * TABLE
 * ./philo 5 800 200 200 [5]
 */
struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_limit_meals;	// [5] | FLAG if -1
	long		start_simulation;		// when we start
	bool		end_simulation;			// a philo dier or all philos full
	bool		all_threads_ready;		// syncro philos
	t_mtx		table_mutex;			// avoid races from reading a table
	t_mtx		write_mutex;			// print mutex
	t_fork		*forks;					// array to forks
	t_philo		*philos;				// all philos
};

// PROTOTYPES

// utils.c
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

// parsing.c
void parse_input(t_table *table, char **argv);

// safe_functions.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode);

// init.c
void	data_init(t_table *table);

// philo.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finish(t_table *table);

// syncro_utils.c
void	wait_all_threads(t_table *table);