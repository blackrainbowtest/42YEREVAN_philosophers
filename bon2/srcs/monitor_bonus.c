#include "philo_bonus.h"

void	death_monitor(t_table *table)
{
	safe_sem_handle(&table->sem->die_sem, WAIT);
	safe_sem_handle(&table->sem->end_sem, POST);
	exit(EXIT_SUCCESS);
}

void	meal_monitor(t_table *table)
{
	long				i;

	if (table->meals_limit <= 0)
		exit(EXIT_SUCCESS);
	i = 0;
	while (i < table->philo_count)
	{
		safe_sem_handle(&table->sem->meal_sem, WAIT);
		++i;
	}
	safe_sem_handle(&table->sem->end_sem, POST);
	exit(EXIT_SUCCESS);
}

void	start_monitors(t_table *table)
{
	pid_t				pid;

	pid = fork();
	if (pid == 0)
		death_monitor(table);
	else
		table->monitor_pid[0] = pid;
	pid = fork();
	if (pid == 0)
		meal_monitor(table);
	else
		table->monitor_pid[1] = pid;
}
