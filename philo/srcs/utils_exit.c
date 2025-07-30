/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:04:18 by root              #+#    #+#             */
/*   Updated: 2025/07/30 22:23:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(const char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error:", 7);
	write(2, msg, len);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	error_manager(int error_code)
{
	if (error_code == EXIT_INVALID_ARG)
		return (write_error("A least one invalid argument."));
	if (error_code == EXIT_MALLOC_FAIL)
		return (write_error("Failed to allocate memory for table."));
	if (error_code == EXIT_MUTEX)
		return (write_error("Fatal error when intializing mutex"));
	if (error_code == EXIT_THREAD_ERROR)
		return (write_error("There was an error creating the threads"));
	return (EXIT_FAILURE);
}
