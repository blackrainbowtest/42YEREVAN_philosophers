/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:58:00 by root              #+#    #+#             */
/*   Updated: 2025/08/03 23:49:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*====COLORS====*/
# define RST "\033[0m"
# define RED "\033[1;31m"
# define G   "\033[1;32m"
# define Y   "\033[1;33m"
# define B   "\033[1;34m"
# define M   "\033[1;35m"
# define C   "\033[1;36m"
# define W   "\033[1;37m"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <limits.h>

# define MAX_PHILOS 200
# define MIN_TIME 60
# define MAX_TIME 900
# define NONE -1

struct					s_table;
typedef pthread_mutex_t	t_mutex;

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

# define SEM_FORKS_NAME "/sem_forks"
# define SEM_WRITE_NAME "/sem_write"
# define SEM_MEAL_NAME "/sem_meal"
# define SEM_FINISH_NAME "/sem_finish"
# define SEM_MEAL_COUNTER_NAME "/sem_meal_counter"

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

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			meals_eaten;
	long		last_meal_time;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	long		start_time;

	t_philo		*philos;

	sem_t		*forks;
	sem_t		*write_lock;
	sem_t		*meal_check;
	sem_t		*finish;
	sem_t		*meal_counter;

	bool		all_alive;
}	t_table;

/* init_bonus.c */
bool	parse_input(int argc, char **argv, t_table *table);
bool	init_table(t_table *table);
bool	init_semaphores(t_table *table);
bool	init_philos(t_table *table);

/* utils_time_bonus.c */
long	get_time_ms(void);

/* utils_text_bonus.c */
int		ft_atoi(const char *str);
bool	is_digit_str(char *str);

/* start_bonus.c */
bool	start_simulation(t_table *table);
void	philo_lifecycle(t_philo *philo);
void	dinner_start(t_table *table);

/* philo_life_bonus.c */
void	print_action(t_philo *philo, char *msg);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_think(t_philo *philo);
void	*monitor_death(void *arg);

#endif /* PHILO_BONUS_H */