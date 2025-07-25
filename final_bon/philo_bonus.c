/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:31:59 by root              #+#    #+#             */
/*   Updated: 2025/07/25 00:44:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		memset(&table, 0, sizeof(t_table));
		parse_input(&table, argv);//OK NO LEAK NO ZOMBIE
		data_init(&table);//OK NO LEAK NO ZOMBIE
		dinner_start(&table);
		clean_exit(&table, NULL, true, EXIT_SUCCESS);//OK NO LEAK NO ZOMBIE
	}
	else
		error_exit(W"Wrong input:\n"G"Correct is ./philo 5 800 200 200 "
			M"[5]"RST);
	return (0);
}
