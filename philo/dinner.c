#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

/**
 * EAT ROUTINE
 * 
 * 1) GRAB THE FORKS
 * 2) EAT WRITE EAT, UPDATE LAST MEAL, UPDATE MEALS COUNTER
 * 3) RELESE THE FORKS
 */
static void	eat(t_philo *philo)
{
	//1)
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	//2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->number_of_limit_meals > 0
		&& philo->meals_counter == philo->table->number_of_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	// 3) 
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/**
 * 1) wait all philos, synchro start
 * 
 * 2) endless loop philo
 */
static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// spinlock
	wait_all_threads(philo->table);
	// synchro with monitor
	// increas a table variable counter, with all threads running
	increase_long(&philo->table->table_mutex,
			&philo->table->threads_running_number); // TODO

	while (!simulation_finish(philo->table))
	{
		// 1) am i full?
		if (philo->full)	// TODO thread safe?
			break ;
		// 2) eat
		eat(philo);
		// 3) sleep -> write_status & presize usleep
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// 4) think
		thinking(philo);
	}
	return (NULL);
}

/**
 * ./philo 5 800 200 200 [0]
 * 
 * 1) If no meals, return (0)
 * 1.1) If only one philo
 * 2) Create all threads, all philos
 * 3) Syncronize beginning of the simulation
 * 		pthread_create->philo,
 * 4)JOIN everyone
 */

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->number_of_limit_meals)
		return ;
	else if (1 == table->number_of_limit_meals)
		; // TODO
	else
	{
		while (++i < table->philo_nbr)
			//     pointer to the philos thread id, function pointer(name), philo, opcode
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	// monitor
	safe_thread_handle(table->monitor, monitor_dinner, table, CREATE); //TODO

	// start of simulation
	table->start_simulation = gettime(MILISECOND);

	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	// wait for everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	// if we manage this line all phylos are full

}