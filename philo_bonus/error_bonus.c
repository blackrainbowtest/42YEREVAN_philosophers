/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:47:37 by root              #+#    #+#             */
/*   Updated: 2025/07/19 16:47:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
