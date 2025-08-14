/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:56:27 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/14 18:56:29 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		status;

	if (argc == 5 || argc == 6)
	{
		status = ft_init(&table, argv);
		if (status != EXIT_SUCCESS)
			return (error_manager(status));
		status = ft_simulate(&table);
		if (status != EXIT_SUCCESS)
			return (error_manager(status));
	}
	else
		return (error_manager(EXIT_INVALID_ARG));
	return (EXIT_SUCCESS);
}
