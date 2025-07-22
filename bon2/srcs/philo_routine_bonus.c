#include "philo_bonus.h"

void	philo_routine(t_philo *philo)
{
	philo->time->born_time = get_time(philo->table, MILLISECOND);
	philo->last_meal = philo->time->born_time;

	// TODO: add die checker thread

	while (true)
	{
		// TODO take fork1
		// TODO take fork2
		// TODO meal
		// TODO drop fork1
		// TODO drop fork2
		// TODO sleep
		// TODO thinking
	}
}