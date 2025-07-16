/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:47:42 by root              #+#    #+#             */
/*   Updated: 2025/07/13 15:48:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief Main function of the philosopher simulation program.
 * 
 * @details
 * This program simulates a dining philosophers problem where philosophers
 * alternate between eating and thinking, while sharing forks. The simulation
 * runs until either a philosopher dies or all philosophers have eaten a
 * specified number of meals.
 * 
 * @note
 * The program expects 5 or 6 command line arguments:
 * - Number of philosophers (5)
 * - Time to die (in milliseconds)
 * - Time to eat (in milliseconds)
 * - Time to sleep (in milliseconds)
 * - [Optional] Number of meals per philosopher
 * should eat (default is unlimited)
 *
 * Example:
 * ./philo 5 800 200 200 [5]
 * 
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return Returns 0 on successful execution, or exits with an error message
 * 
 * @see parse_input()
 * @see data_init()
 * @see dinner_start()
 * @see clean()
 * @see error_exit()
 */
int	main(int argc, char **argv)
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
		error_exit("Wrong input:\n"G"Correct is ./philo 5 800 200 200 [5]"RST);
	return (0);
}
