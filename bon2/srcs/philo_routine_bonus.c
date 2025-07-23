#include "philo_bonus.h"

void	*die_checker_routine(void *arg)
{
	t_philo	*philo;
	long	now;
	long	last_meal;
	long	time_to_die;

	philo = (t_philo *)arg;
	time_to_die = philo->table->time->time_to_die;
	while (true)
	{
		usleep(1000);
		now = get_time(philo->table, MILLISECOND);
		last_meal = philo->time_last_meal;
		if (now - last_meal > time_to_die)
		{
			write_status(DIED, philo, true);
			safe_sem_handle(&philo->table->sem->fork_sem, POST);
		}
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	philo->time_born = get_time(philo->table, MILLISECOND);
	philo->time_last_meal = philo->time_born;

	while (true)
	{
		/* TODO */
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}