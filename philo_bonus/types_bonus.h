
#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <semaphore.h>

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;

	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*meal_check;

	long			start_time;
	pid_t			*pids;
}	t_table;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	t_table			*table;
}	t_philo;
#endif