#include "philo_bonus.h"

static void	dead_checker_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (true)
	{
		sem_wait(philo->table->sem->die_sem);
		if (get_time(table, MILLISECOND) - philo->time_last_meal > table->time->time_to_die)
		{
			write_status(DIED, philo, true);
			sem_wait(philo->table->sem->write_sem);
			sem_post(philo->table->sem->end_sem);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->table->sem->write_sem);
	}
	return (NULL);
}

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

static void	run_simulation(t_table *table, long index)
{
	pthread_t	dead_checker;
	t_philo		*philo;

	philo = table->philos[index];
	if(pthread_create(&dead_checker, NULL, dead_checker_routine, philo) != 0)
		clean_exit(table, C"pthread_create"RED" failed\n"RST, true, EXIT_FAILURE);
	if (pthread_detach(dead_checker))
		clean_exit(table, C"pthread_detach"RED" failed\n"RST, true, EXIT_FAILURE);
	
	philo->time_born = get_time(table, MILLISECOND);
	philo->time_last_meal = get_time(table, MILLISECOND);
	while (true)
		philo_routine(philo);
}

void	dinner_start(t_table *table)
{
	long		i;
	pthread_t	meal_checker;
	
	if (table->meals_limit > 0)
	{
		if(pthread_create(&meal_checker, NULL, meal_checker_routine, table) != 0)
			clean_exit(table, C"pthread_create"RED" failed\n"RST, true, EXIT_FAILURE);
		if (pthread_detach(meal_checker))
			clean_exit(table, C"pthread_detach"RED" failed\n"RST, true, EXIT_FAILURE);
	}
	// new thread watch for end_sem if end_sem is posted, then exit
	i = -1;
	while (++i < table->philo_count)
	{
		table->pid[i] = fork();
		if (table->pid[i] < 0)
			clean_exit(table, C"Fork"RED" failed\n"RST, true, EXIT_FAILURE);
		if (table->pid[i] == 0)
			run_simulation(table, i);
	}
	waitpid(-1, NULL, 0);
}