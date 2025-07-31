/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 16:04:18 by root              #+#    #+#             */
/*   Updated: 2025/07/31 00:09:32 by root             ###   ########.fr       */
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
		return (write_error(INVALID_ARG));
	if (error_code == EXIT_MALLOC_FAIL)
		return (write_error(MALLOC_FAIL));
	if (error_code == EXIT_MUTEX)
		return (write_error(MUTEX_ERROR));
	if (error_code == EXIT_THREAD_ERROR)
		return (write_error(THREAD_ERROR));
	if (error_code == EXIT_INT_ERROR)
		return (write_error(INT_ERROR));
	if (error_code == EXIT_INPUT_ERROR)
		return (write_error(INPUT_ERROR));
	if (error_code == EXIT_EMPTY_ERROR)
		return (write_error(EMPTY_ERROR));
	if (error_code == EXIT_NEGATIVE_ERROR)
		return (write_error(NEGATIVE_ERROR));
	return (EXIT_FAILURE);
}
