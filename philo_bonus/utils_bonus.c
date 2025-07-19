/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:04:03 by root              #+#    #+#             */
/*   Updated: 2025/07/19 16:08:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Returns the current time in the requested unit.
 * 
 * Retrieves the current system time using `gettimeofday` and returns it
 * as a `long` in seconds, milliseconds, or microseconds depending on the
 * specified `time_code`.
 * 
 * @param time_code Time unit to return: SECOND, MILLISECOND, or MICROSECOND.
 * @return Current time in the specified unit as a `long`.
 * 
 * @note The function exits with an error if `gettimeofday` fails or if
 * an invalid time code is passed.
 * 
 * @see t_time_code, gettimeofday(), error_exit()
 */
long	gettime(t_time_code time_code)
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
		error_exit("Wrong input to gettime");
	return (42);
}