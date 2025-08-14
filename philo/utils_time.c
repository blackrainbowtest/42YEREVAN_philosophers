/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:57:06 by aramarak          #+#    #+#             */
/*   Updated: 2025/08/14 18:57:08 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	ft_time_from_last_meal(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_table *table)
{
	long long	i;

	i = get_time();
	while (!(table->someone_died))
	{
		if (ft_time_from_last_meal(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}

void	precise_usleep(long usec)
{
	long	start;
	long	elapsed;
	long	rem;

	start = get_time();
	while (get_time() - start < usec)
	{
		elapsed = get_time() - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (get_time() - start < usec)
				;
		}
	}
}
