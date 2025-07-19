/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:32:00 by root              #+#    #+#             */
/*   Updated: 2025/07/19 16:36:46 by root             ###   ########.fr       */
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