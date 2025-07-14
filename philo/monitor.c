#include "philo.h"

/**
 * @brief Checks if the philosopher has died from starvation.
 * 
 * Calculates the time elapsed since the philosopher's last meal and compares
 * it to the configured time to die. If the philosopher has eaten all required
 * meals (is full), the function returns false. Access to shared variables is
 * synchronized with a mutex.
 * 
 * @param philo Pointer to the philosopher structure.
 * @return true if the philosopher has died, false otherwise.
 * 
 * @note Time is measured in milliseconds. `time_to_die` is originally in 
 * microseconds and is converted back to milliseconds for comparison.
 */
static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	monitor_dinner(void *data)
{
	int		i;
	t_table *table;

	i = -1;
	table = (t_table *)data;
	// make sure all philo running
	// spinlock till all thread run
	while (!all_threads_running(&table->table_mutex, &table->threads_running_number,
			table->philo_nbr))
		;
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finish(table))
		{
			if (philo_died(table->philos + i)) //TODO
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
}
