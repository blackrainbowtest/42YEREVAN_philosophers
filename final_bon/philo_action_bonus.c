#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->fork_sem, WAIT);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
	safe_sem_handle(&philo->table->sem->fork_sem, WAIT);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
}

void	philo_eat(t_philo *philo)//TODO
{
	write_status(EATING, philo, DEBUG_MODE);
	safe_sem_handle(&philo->table->sem->die_sem, WAIT);
	philo->time_last_meal = get_time(philo->table, MILLISECOND);
	philo->meals_eaten++;
	safe_sem_handle(&philo->table->sem->die_sem, POST);
	if (philo->table->meals_limit > 0
		&& philo->meals_eaten >= philo->table->meals_limit)
	{
		philo->full = true;
		safe_sem_handle(&philo->table->sem->end_sem, POST);
	}
	// time_to_eat = philo->table->time->time_to_eat;
	// philo->time_last_meal = get_time(philo->table, MILLISECOND);
	// philo->meals_eaten++;
	// if (philo->table->meals_limit > 0
	// 	&& philo->meals_eaten >= philo->table->meals_limit)
	// {
	// 	philo->full = true;
	// 	safe_sem_handle(&philo->table->sem->meal_sem, POST);
	// }
	// precise_usleep(time_to_eat * 1e3, philo->table);
}

void	drop_forks(t_philo *philo)
{
	safe_sem_handle(&philo->table->sem->fork_sem, POST);
	safe_sem_handle(&philo->table->sem->fork_sem, POST);
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

void	philo_think(t_philo *philo)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!simulation_finish(philo->table))
		write_status(THINKING, philo, DEBUG_MODE);
	t_eat = philo->table->time->time_to_eat;
	t_sleep = philo->table->time->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}
