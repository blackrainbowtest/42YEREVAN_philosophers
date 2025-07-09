#include "philo.h"
/**
 * ./philo 5 800 200 200 [5]
 */
int main(int argc, char **argv)
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		// errors checking
		parse_input(&table, argv);
		// creating the actual thing
		data_init(&table);
		// main simulation
		dinner_start(&table);	// TODO
		// no leaks -> 1 philo died or all philos full
		clean(&table);	// TODO
	}
	else
	{
		error_exit("Wrong input:\n"G"Correct is ./philo 5 800 200 200 [5]"RST);
	}
}