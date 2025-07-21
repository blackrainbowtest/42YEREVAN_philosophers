#include "philo_bonus.h"

void	cleanup_semaphores(void)
{
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_WRITE);
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}

void	clean_exit(t_table *table, const char *msg, bool is_parent, int exit_code)
{
	long	i;

	if (is_parent && table->pid)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			if (table->pid[i] > 0)
				kill(table->pid[i], SIGKILL);
		}
	}
	if (table->sem)
	{

	}
	if (table->philos)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			if (table->philos[i])
				free(table->philos[i]);
		}
		free(table->philos);
	}
	if (table->pid)
		free(table->pid);
	free(table->time);
	if (msg)
		printf("%s", msg);
	exit(exit_code);
}