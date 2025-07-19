/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:32:00 by root              #+#    #+#             */
/*   Updated: 2025/07/19 23:34:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Allocates memory safely and exits on failure.
 * 
 * Wraps the standard `malloc` function and verifies that the returned pointer
 * is not NULL. If memory allocation fails, the program exits with an error 
 * message.
 * 
 * @param bytes Number of bytes to allocate.
 * @return A non-NULL pointer to the allocated memory block.
 * 
 * @note This function is used throughout the simulation to ensure memory 
 * allocation
 * is always checked and never silently fails.
 * 
 * @see error_exit()
 */
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}

void	safe_sem_handle(sem_t **sem, t_opcode action)
{
	if (!sem || !*sem)
		error_exit("safe_sem_handle: invalid semaphore");

	if (action == WAIT)
	{
		if (sem_wait(*sem) == -1)
			error_exit("sem_wait() failed");
	}
	else if (action == POST)
	{
		if (sem_post(*sem) == -1)
			error_exit("sem_post() failed");
	}
	else
	{
		error_exit("safe_sem_handle: unknown action");
	}
}