/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:58:03 by root              #+#    #+#             */
/*   Updated: 2025/08/03 23:46:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	cleanup(t_table *table)
{
	for (int i = 0; i < table->philo_count; i++)
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
	dinner_start(&table);      // ⏳ Ожидает завершения внутри
	cleanup(&table);           // ✅ Очистка после завершения
	return (EXIT_SUCCESS);
}
