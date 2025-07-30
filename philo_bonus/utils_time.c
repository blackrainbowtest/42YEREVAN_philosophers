#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	ft_time_from_last_meal(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_table *table)
{
	long long	i;

	i = get_time();
	while (!(table->someone_died))
	{
		if (ft_time_from_last_meal(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}