#include "philo_bonus.h"

void	*die_checker_routine(void *arg)
{
	t_philo	*philo;
	long	now;
	long	last_meal;
	long	time_to_die;

	philo = (t_philo *)arg;
	time_to_die = philo->time->time_to_die;
	while (true)
	{
		usleep(1000);
		now = get_time(philo->table, MILLISECOND);
		last_meal = philo->time_last_meal;
		if (now - last_meal > time_to_die)
		{
			write_status(DIED, philo, true);
			sem_post(philo->table->sem->die_sem);
		}
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	die_checker;

	philo->time->born_time = get_time(philo->table, MILLISECOND);
	philo->last_meal = philo->time->born_time;

	// TODO: add die checker thread
	if (pthread_create(&die_checker, NULL, &die_checker_routine, philo) != 0)
	{
		safe_sem_handle(&philo->table->sem->write_sem, WAIT);
		printf(RED"Thread creation failed\n"RST);
		safe_sem_handle(&philo->table->sem->write_sem, POST);
		exit(EXIT_FAILURE);
	}
	pthread_detach(die_checker);

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