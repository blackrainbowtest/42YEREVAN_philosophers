#include "philo_bonus.h"

void	dinner_start(t_table *table)
{
	long	i;
	
	table->time->time_to_start = get_time(table, MILLISECOND);
	i = -1;
	while (++i < table->philo_count)
	{
		table->pid[i] = fork();
		if (table->pid[i] < 0)
			clean_exit(table, RED"Fork failed\n"RST, true, EXIT_FAILURE);
		else if (table->pid[i] == 0)
		{
			philo_routine(table->philos[i]);//TODO
			exit(EXIT_SUCCESS);
		}
	}

}