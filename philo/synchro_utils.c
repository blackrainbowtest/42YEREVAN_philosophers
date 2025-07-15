#include "philo.h"

/**
 * SPINLOCK
 * @brief Waits until all philosopher threads are ready to start.
 * 
 * Continuously checks the `all_threads_ready` flag in a thread-safe way,
 * blocking execution until the flag becomes true. This ensures that the
 * simulation does not start before all threads have been initialized.
 * 
 * @param table Pointer to the main simulation table.
 * 
 * @note This function performs a busy-wait (spinlock) and assumes that another
 * thread will eventually set `all_threads_ready` to true via `set_bool()`.
 * 
 * @see get_bool(), set_bool()
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

/**
 * @brief Checks whether all philosopher threads have started.
 * 
 * Safely compares the current number of running threads to the expected number
 * of philosophers. Uses a mutex to ensure thread-safe access to the shared
 * `threads_running_number` variable.
 * 
 * @param mutex Pointer to the mutex protecting the counter.
 * @param threads Pointer to the variable tracking number of running threads.
 * @param philo_nbr Total number of philosophers expected to run.
 * @return true if all philosopher threads are running, false otherwise.
 * 
 * @see safe_mutex_handle()
 */
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Safely increments a long integer with mutex protection.
 * 
 * Locks the provided mutex, increments the long variable by one,
 * and unlocks the mutex. Ensures thread-safe increment of shared counters.
 * 
 * @param mutex Pointer to the mutex protecting the variable.
 * @param value Pointer to the long variable to increment.
 * 
 * @note Commonly used to increment values such as `threads_running_number`
 * or per-philosopher meal counters in a thread-safe manner.
 * 
 * @see safe_mutex_handle()
 */
void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Desynchronizes philosopher threads to prevent contention.
 * 
 * Applies a small delay to certain philosophers at the beginning of the simulation
 * to avoid all of them trying to grab forks at the same time, which may cause
 * deadlocks or excessive contention.
 * 
 * - If the number of philosophers is even: even-numbered philosophers sleep briefly.
 * - If the number is odd: odd-numbered philosophers enter thinking state first.
 * 
 * @param philo Pointer to the philosopher structure.
 * 
 * @note Helps to stagger thread execution and reduce resource collisions.
 * 
 * @see precise_usleep(), thinking()
 */
void	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}