#include "philo.h"

/**
 * SPINLOCK to synchronize philos start
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}