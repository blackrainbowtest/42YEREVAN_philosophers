#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->forks, WAIT);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
	safe_sem_handle(&philo->table->sem->forks, WAIT);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
}

void	philo_eat(t_philo *philo)
{
	long	time_to_eat;

	time_to_eat = philo->table->time->time_to_eat;
	philo->time_last_meal = get_time(philo->table, MILLISECOND);
	write_status(EATING, philo, DEBUG_MODE);
	philo->meals_counter++;
	if (philo->table->max_meals > 0
		&& philo->meals_counter >= philo->table->max_meals)
	{
		philo->full = true;
		safe_sem_handle(&philo->table->sem->meal_sem, POST);
	}
	precise_usleep(time_to_eat * 1e3, philo->table);
}

void	drop_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->forks, POST);
	safe_sem_handle(&philo->table->sem->forks, POST);
}

void	philo_sleep(t_philo *philo)
{
	long	time_to_sleep;

	time_to_sleep = philo->table->time->time_to_sleep;
	if (simulation_finish(philo->table))
		return ;
	write_status(SLEEPING, philo, DEBUG_MODE);
	precise_usleep(time_to_sleep * 1e3, philo->table);
}
