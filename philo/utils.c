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

/**
 * precise usleep, the real one suck
 * 
 * why table is simulation finish?
 * 
 * 1) usleep the majorty of time, not CPU intensive
 * 2) refine last microsec with spinlock
 *                    (ինչքան միկրովարկյան քնել, ընդհանուր ստրուկտուրա)
 */
void	precise_usleep(long usec, t_table *table)
{
	long	start;		// սպասման ժամանակի մեկնարկային կետը (միկրովարկյաններով)
	long	elapsed;	// ինչքան ժամանակ է անցել մեկնարկից սկսած
	long	rem;		// remaining ինչքան է դեռ մնացել սպասելու

	start = gettime(MICROSECOND);
	// ցիկլը աշխատում է քանի դեռ մեկնարկից չի անցել քնելու չափ ժամանակ
	while (gettime(MICROSECOND) - start < usec)
	{
		// եթե քնելու ընթացքում սիմուլացիան ավարտվել է, դուրս գալ ցիկլից
		if (simulation_finish(table))
			break ;
		// ինչքան է անցել մեկնարկից հետո
		elapsed = gettime(MICROSECOND) - start;
		// ինչքան է մնացել դեռ քնելու
		rem = usec - elapsed;

		// Եթե մնացել է սպասելու ավելի քան 1000 միկրովարկյան ազատում ենք cpy 
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			// SPINLOCK - ակտիվ սպասողական վիճակ
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	*clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}