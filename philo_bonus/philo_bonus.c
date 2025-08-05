/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:58:03 by root              #+#    #+#             */
/*   Updated: 2025/08/05 19:06:05 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	cleanup(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		kill(table->philos[i].pid, SIGKILL);
	sem_close(table->forks);
	sem_close(table->write_lock);
	sem_close(table->meal_check);
	sem_close(table->finish);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_meal");
	sem_unlink("/sem_finish");
	free(table->philos);
}

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
	dinner_start(&table);
	cleanup(&table);
	return (EXIT_SUCCESS);
}
