#include "philo_bonus.h"

void	start_monitors(t_table *table)
{
	pid_t				pid;

	pid = fork();
	if (pid == 0)
		death_monitor(table);//TODO
	pid = fork();
	if (pid == 0)
		meal_monitor(table);//TODO
}
