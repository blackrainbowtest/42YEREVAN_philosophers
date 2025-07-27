/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:48:43 by root              #+#    #+#             */
/*   Updated: 2025/07/27 21:34:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		status;

	if (argc == 5 || argc == 6)
	{
		ft_init(&table, argv);
		// ft_simulate(&table);
	}
	else
		return (error_manager(EXIT_INVALID_ARG));
	return (EXIT_SUCCESS);
}