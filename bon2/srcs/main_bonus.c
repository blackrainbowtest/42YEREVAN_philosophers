#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	*p_table;
	
	if (argc == 5 || argc == 6)
	{
		parse_input(&p_table, argv);
		data_init(&p_table);
		// simulation_start(&p_table);//TODO
		clean_exit(&p_table, NULL, true, EXIT_SUCCESS);
	}
	else
		error_exit(W"Wrong input:\n"G"Correct is ./philo 5 800 200 200 "M"[5]"RST);
	return (0);
}