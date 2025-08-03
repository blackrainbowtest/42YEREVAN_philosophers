/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:58:03 by root              #+#    #+#             */
/*   Updated: 2025/08/03 16:17:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!parse_input(argc, argv, &table))
		return (printf(RED "Error: " RST INPUT_ERROR "\n"), EXIT_INPUT_ERROR);
	if (!init_table(&table))
		return (printf(RED "Error: " RST MALLOC_FAIL "\n"), EXIT_TABLE_INIT);
	if (!init_semaphores(&table))
		return (printf(RED "Error: " RST "Failed to initialize semaphores.\n"),
			EXIT_MUTEX);
	if (!init_philos(&table))
		return (printf(RED "Error: " RST "Failed to initialize philos.\n"),
			EXIT_PHILO_INIT);
	
	for (int i = 0; i < table.philo_count; i++)
		printf("Philo %d: meals=%d, last_meal=%ld\n",
			table.philos[i].id,
			table.philos[i].meals_eaten,
			table.philos[i].last_meal_time);
}
