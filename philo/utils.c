#include "philo.h"

/**
 * gettimeofday // January 1, 1970
 * time_code -> SECONDS, MILISECONDS, MICROSECONDS
 */
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday filed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (42);
}

void	precise_usleep(long usec, t_table *table)
{
	
}

/**
 * precise usleep, the real one suck
 * 
 * why table is simulation finish?
 * 
 * 1) usleep the majorty of time, not CPU intensive
 * 2) refine last microsec with spinlock
 */
void	precise_usleep(long usec, t_table *table)
{

}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}