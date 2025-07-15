/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:40:17 by root              #+#    #+#             */
/*   Updated: 2025/07/15 23:40:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/**
 * @brief Sleeps precisely for a given time, checking simulation status.
 * 
 * Implements an accurate sleep function in microseconds. It periodically
 * checks whether the simulation should end, and avoids using a full `usleep`
 * if the remaining time is small, switching to active spinning for precision.
 * 
 * This prevents the thread from sleeping too long and missing critical events
 * like a philosopher dying.
 * 
 * @param usec Time to sleep in microseconds.
 * @param table Pointer to the simulation table, used to check simulation status.
 * 
 * @note For large sleep durations, it halves the delay and uses `usleep()`;
 * for small remaining times, it switches to a spin-wait loop.
 * 
 * @see simulation_finish(), gettime(), usleep()
 */
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finish(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

/**
 * @brief Frees all allocated resources and destroys all mutexes.
 * 
 * Iterates through each philosopher and destroys their individual mutex.
 * Then destroys global simulation mutexes (`write_mutex`, `table_mutex`) and
 * frees the dynamically allocated memory for philosophers and forks.
 * 
 * @param table Pointer to the simulation table containing all resources.
 * 
 * @note Should be called once the simulation is finished to avoid memory leaks
 * or dangling mutexes.
 * 
 * @see safe_mutex_handle(), free()
 */
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

/**
 * @brief Prints an error message in red and exits the program.
 * 
 * Outputs the provided error message to standard output using red color
 * formatting, then immediately terminates the program with `EXIT_FAILURE`.
 * 
 * @param error The error message to display before exiting.
 * 
 * @note This function does not return. It is used to handle fatal errors
 * such as failed memory allocation or threading issues.
 * 
 * @see exit(), printf()
 */
void	error_exit(const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}
