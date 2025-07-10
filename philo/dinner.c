#include "philo.h"

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

	while (!simulation_finish(philo->table))
	{
		// 1) am i full?
		if (philo->full)	// TODO thread safe?
			break ;
		// 2) eat
		eat(philo);
		// 3) sleep -> write_status & presize usleep
		
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
	// start of simulation
	table->start_simulation = gettime(MILISECOND);

	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	// wait for everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i], NULL, NULL, JOIN);
	// if we manage this line all phylos are full

}