/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:53:15 by root              #+#    #+#             */
/*   Updated: 2025/07/28 00:29:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**https://github.com/Gaspachow/philosophers-42 */
#include "philo.h"

void	*ft_thread()
{
	
}

int	ft_simulate(t_table *table)
{
	long	i;
	t_philo	*philos;

	i = 0;
	philos = table->philos;
	table->start_time = get_time();
	while (i < table->philo_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, ft_thread, &(philos[i])))
			return (EXIT_FAILURE);
		philos[i].last_meal_time = get_time();
		++i;
	}
	// death
	// exit
	return (EXIT_SUCCESS);
}