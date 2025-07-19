
#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <semaphore.h>

struct s_table;

typedef struct s_philo
{
	pid_t				pid;
	int					id;
	long				last_meal_time;
	int					meals_counter;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_limit_meals;

	long			start_time;
	bool			end_simulation;
	pid_t			*pids;

	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*meal_check;
	sem_t			*finish;

	t_philo			*philos;
}	t_table;


#endif