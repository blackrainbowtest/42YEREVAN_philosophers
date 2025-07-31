/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:04:18 by root              #+#    #+#             */
/*   Updated: 2025/07/31 23:10:49 by root             ###   ########.fr       */
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
		exit (write_error(INVALID_ARG));
	if (error_code == EXIT_MALLOC_FAIL)
		exit (write_error(MALLOC_FAIL));
	if (error_code == EXIT_MUTEX)
		exit (write_error(MUTEX_ERROR));
	if (error_code == EXIT_THREAD_ERROR)
		exit (write_error(THREAD_ERROR));
	if (error_code == EXIT_INT_ERROR)
		exit (write_error(INT_ERROR));
	if (error_code == EXIT_INPUT_ERROR)
		exit (write_error(INPUT_ERROR));
	if (error_code == EXIT_EMPTY_ERROR)
		exit (write_error(EMPTY_ERROR));
	if (error_code == EXIT_NEGATIVE_ERROR)
		exit (write_error(NEGATIVE_ERROR));
	if (error_code == EXIT_ZERO_ERROR)
		exit (write_error(ZERO_ERROR));
	exit (write_error(UNKNOWN_ERROR));
}
