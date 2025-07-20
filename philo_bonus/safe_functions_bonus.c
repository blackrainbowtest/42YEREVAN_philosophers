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

static void	handle_sem_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (WAIT == opcode || POST == opcode))
		error_exit("Semaphore is not valid or not initialized.");
	else if (status == EINVAL && CREATE == opcode)
		error_exit("Semaphore attribute or name is invalid.");
	else if (status == EINTR && WAIT == opcode)
		error_exit("Semaphore wait was interrupted by a signal.");
	else if (status == EACCES)
		error_exit("Permission denied to access the semaphore.");
	else if (status == EOVERFLOW)
		error_exit("Semaphore value exceeds SEM_VALUE_MAX.");
	else
		error_exit("Unexpected semaphore error.");
}

void	safe_sem_handle(sem_t **sem, t_opcode opcode)
{
	int	status;

	if (!sem || !*sem)
		error_exit("safe_sem_handle: invalid semaphore");

	errno = 0;
	if (opcode == WAIT)
		status = sem_wait(*sem);
	else if (opcode == POST)
		status = sem_post(*sem);
	else if (opcode == CLOSE)
		status = sem_close(*sem);
	else
		error_exit("safe_sem_handle: unknown opcode");

	if (status == -1)
		handle_sem_error(errno, opcode);
}

sem_t	*safe_sem_open(const char *name, int oflag, mode_t mode, unsigned int value)
{
	sem_t	*sem;

	errno = 0;
	sem = sem_open(name, oflag, mode, value);
	if (sem == SEM_FAILED)
	{
		if (errno == EEXIST)
			error_exit("Semaphore already exists.");
		else if (errno == ENOENT)
			error_exit("Semaphore does not exist.");
		else if (errno == EACCES)
			error_exit("Permission denied to create or open semaphore.");
		else if (errno == ENFILE || errno == EMFILE)
			error_exit("Too many file descriptors in use.");
		else if (errno == ENOMEM)
			error_exit("Not enough memory to create semaphore.");
		else
			error_exit("sem_open() failed unexpectedly.");
	}
	return (sem);
}

void	safe_sem_unlink(const char *name)
{
	if (sem_unlink(name) == -1)
	{
		if (errno == ENOENT)
			error_exit("Semaphore does not exist (sem_unlink).");
		else if (errno == EACCES)
			error_exit("Permission denied to unlink semaphore.");
		else
			error_exit("sem_unlink() failed unexpectedly.");
	}
}