/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:40:17 by root              #+#    #+#             */
/*   Updated: 2025/07/26 17:07:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Handles the philosopher's thinking phase with optional delay.
 * 
 * Logs the THINKING status (if simulation has started) and optionally performs a
 * calculated pause to help balance the timing of eating/sleeping when the 
 * number of philosophers is odd.
 * 
 * - For even philosopher counts: returns immediately with no delay.
 * - For odd counts: calculates thinking time as (2 * time_to_eat - 
 * time_to_sleep),
 *   adjusted by a 0.42 coefficient for simulation balance.
 * 
 * @param philo Pointer to the philosopher structure.
 * @param pre_simulation Set to true if this is called before the simulation 
 * starts.
 *                       In this case, status is not printed.
 * 
 * @note This function helps desynchronize philosopher actions in odd-numbered 
 * simulations.
 * 
 * @see write_status(), precise_usleep(), simulation_finish()
 */
void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation && !simulation_finish(philo->table))
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

/**
 * @brief Handles the special case of a single philosopher.
 * 
 * In the dining philosophers problem, a lone philosopher cannot eat since
 * they only have access to one fork. This function simulates their behavior
 * accordingly: they take one fork, then wait until the simulation ends (due
 * to death timeout or external termination).
 * 
 * Steps:
 * - Waits for all threads to be ready.
 * - Sets the last_meal_time to current time.
 * - Increments the count of running threads.
 * - Logs the action of taking the first fork.
 * - Enters a loop waiting for simulation to end.
 * 
 * @param arg Pointer to the `t_philo` structure (cast from `void*`).
 * @return Always returns NULL.
 * 
 * @note This function is launched in its own thread for the lone 
 * philosopher case.
 * 
 * @see wait_all_threads(), simulation_finish(), write_status()
 */
void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_number);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finish(philo->table))
		usleep(200);
	return (NULL);
}

/**
 * @brief Performs the eating routine of a philosopher.
 * 
 * The philosopher attempts to lock both forks (first and second), then:
 * - Logs taking each fork.
 * - Updates the `last_meal_time`.
 * - Increments the `meals_counter`.
 * - Logs the EATING status.
 * - Sleeps for `time_to_eat` using `precise_usleep()`.
 * - If a meal limit is defined and reached, sets `full = true`.
 * - Unlocks both forks after eating.
 * 
 * @param philo Pointer to the philosopher structure.
 * 
 * @note Uses mutexes to ensure exclusive access to forks and meal data.
 *       This function is the critical section of the philosopher lifecycle.
 * 
 * @see safe_mutex_handle(), write_status(), precise_usleep()
 */
static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->number_of_limit_meals > 0
		&& philo->meals_counter == philo->table->number_of_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/**
 * @brief Main routine executed by each philosopher thread.
 * 
 * Waits for all threads to be ready, initializes philosopher's last meal time,
 * and enters the life cycle loop: eat → sleep → think. Exits the loop if:
 * - The philosopher has eaten the required number of meals (`philo->full`)
 * - The simulation is marked as finished (`simulation_finish`)
 * 
 * Also uses `de_synchronize_philos()` to avoid thread collisions on startup.
 * 
 * @param data Pointer to the philosopher (`t_philo`), cast from `void *`.
 * @return Always returns NULL (pthread-compatible).
 * 
 * @note This function is launched as a thread per philosopher.
 * 
 * @see eat(), thinking(), write_status(), simulation_finish()
 */
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime(MILLISECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_number);
	de_synchronize_philos(philo);
	while (!simulation_finish(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

/**
 * @brief Starts the philosopher simulation.
 * 
 * Initializes and launches all philosopher threads and the monitoring thread.
 * Handles special case for a single philosopher, and waits for all threads to
 * complete before marking the simulation as finished.
 * 
 * Steps:
 * - If the number of required meals is zero, exits immediately.
 * - Launches either a lone philosopher thread or multiple philosopher threads.
 * - Starts the monitor thread.
 * - Records the simulation start time.
 * - Signals all threads to begin execution.
 * - Waits for all philosopher threads to finish.
 * - Signals end of simulation and waits for monitor thread to join.
 * 
 * @param table Pointer to the simulation context.
 * 
 * @note This is the main orchestration function for the simulation.
 * 
 * @see dinner_simulation(), monitor_dinner(), lone_philo(), safe_thread_handle()
 */
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->number_of_limit_meals)
		return ;
	else if (1 == table->philo_nbr)
		safe_thread_handle(&table->philos[0].thread_id, lone_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
