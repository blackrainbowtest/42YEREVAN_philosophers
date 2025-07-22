#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->forks, WAIT);
	write_status(TAKE_FORK, philo, false);
	safe_sem_handle(&philo->table->sem->forks, WAIT);
	write_status(TAKE_FORK, philo, false);
}

void	philo_eat(t_philo *philo)
{
	philo->time_last_meal = get_time(philo->table, MILLISECOND);
	write_status(EATING, philo, false);
	philo->meals_counter++;
	if (philo->table->max_meals > 0
		&& philo->meals_counter >= philo->table->max_meals)
	{
		philo->full = true;
		safe_sem_handle(&philo->table->sem->meal_sem, POST);
	}
	precise_usleep(philo->table->time->time_to_eat * 1e3, philo->table);
}