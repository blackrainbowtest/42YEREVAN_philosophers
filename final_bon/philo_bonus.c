/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:31:59 by root              #+#    #+#             */
/*   Updated: 2025/07/31 19:42:58 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		memset(&table, 0, sizeof(t_table));
		parse_input(&table, argv);
		data_init(&table);
		dinner_start(&table);
		clean_exit(&table, NULL, EXIT_SUCCESS);
	}
	else
		error_exit(W"Wrong input:\n"G"Correct is ./philo 5 800 200 200 "
			M"[5]"RST);
	return (EXIT_SUCCESS);
}
