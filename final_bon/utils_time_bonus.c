/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:32:17 by root              #+#    #+#             */
/*   Updated: 2025/07/22 00:32:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(t_table *p_table, t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday filed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		clean_exit(p_table, "Wrong input to "RED
			"GETTIME"RST" Error\n", EXIT_FAILURE);
	return (42);
}

void	precise_usleep(long usec, t_philo *philo)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time(philo->table, MICROSECOND);
	while (get_time(philo->table, MICROSECOND) - start < usec)
	{
		elapsed = get_time(philo->table, MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time(philo->table, MICROSECOND) - start < usec)
				;
		}
	}
}
