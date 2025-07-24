#include "philo_bonus.h"

static void	*meal_checker_routine(void *arg)
{
	t_table	*table;
	long	full_count;

	table = (t_table *)arg;
	while (true)
	{
		safe_sem_handle(&table->sem->meal_sem, WAIT);
		++full_count;
		if (full_count >= table->philo_count)
			clean_exit(table, G"All philos are full\n"RST, true, EXIT_SUCCESS);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	long		i;
	pthread_t	meal_checker;
	
	table->time->time_to_start = get_time(table, MILLISECOND);
	if (table->meals_limit > 0)
	{
		if(pthread_create(&meal_checker, NULL, meal_checker_routine, table) != 0)
			clean_exit(table, C"pthread_create"RED" failed\n"RST, true, EXIT_FAILURE);
		if (pthread_detach(meal_checker))
			clean_exit(table, C"pthread_detach"RED" failed\n"RST, true, EXIT_FAILURE);
	}
	i = -1;
	while (++i < table->philo_count)
	{
		table->pid[i] = fork();
		if (table->pid[i] < 0)
			clean_exit(table, C"Fork"RED" failed\n"RST, true, EXIT_FAILURE);
		else if (table->pid[i] == 0)
		{
			philo_routine(table->philos[i]);
			exit(EXIT_SUCCESS);
		}
	}
}