#include "philo_bonus.h"

void	*die_checker_routine(void *arg)
{
	t_philo	*philo;
	long	now;
	long	last_meal;
	long	time_to_die;

	philo = (t_philo *)arg;
	last_meal = philo->time_last_meal;
	time_to_die = philo->time->time_to_die;
	while (true)
	{
		usleep(1000);
		now = get_time(philo->table, MILLISECOND);
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
		sem_wait(philo->table->sem[SEM_WRITE]);
		printf(RED"Thread creation failed\n"RST);
		sem_post(philo->table->sem[SEM_WRITE]);
		exit(EXIT_FAILURE);
	}
	pthread_detach(die_checker);

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