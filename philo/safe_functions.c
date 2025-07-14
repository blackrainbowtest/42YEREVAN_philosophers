/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 01:51:02 by root              #+#    #+#             */
/*   Updated: 2025/07/15 01:53:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/**
 * @brief Handles errors returned by POSIX mutex operations.
 * 
 * Interprets the error code (`status`) returned by mutex-related functions
 * (`pthread_mutex_init`, `lock`, `unlock`, `destroy`) and exits the program
 * with a descriptive error message if an error is detected.
 * 
 * The behavior depends on the operation type (`opcode`) to provide context-aware
 * messages.
 * 
 * @param status Return code from a POSIX mutex function.
 * @param opcode The operation that was attempted: INIT, LOCK, UNLOCK, 
 * or DESTROY.
 * 
 * @note If `status == 0`, the function returns immediately (no error).
 * 
 * @see safe_mutex_handle(), error_exit(), t_opcode
 */
static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread"
			" blocked waiting for mutex");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough to"
			" create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

/**
 * @brief Safely handles mutex operations: init, lock, unlock, and destroy.
 * 
 * Wraps standard POSIX mutex functions (`pthread_mutex_*`) and performs
 * error checking via `handle_mutex_error`. This function allows uniform
 * and safe management of all mutex operations using a single interface.
 * 
 * @param mutex Pointer to the mutex to be manipulated.
 * @param opcode Operation to perform: INIT, LOCK, UNLOCK, or DESTROY.
 * 
 * @note If an invalid opcode is provided, the program will exit with an error.
 * 
 * @see handle_mutex_error(), t_opcode, pthread_mutex_init(), 
 * pthread_mutex_lock()
 */
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

/**
 * @brief Handles errors returned by POSIX thread functions.
 * 
 * Interprets the error code (`status`) returned by pthread functions such as
 * `pthread_create`, `pthread_join`, and `pthread_detach`, and exits the program
 * with a human-readable error message if an error occurred.
 * 
 * The behavior depends on the operation type (`opcode`) to distinguish between
 * errors during thread creation, joining, or detaching.
 * 
 * @param status Return code from a pthread function.
 * @param opcode Operation type: CREATE, JOIN, or DETACH.
 * 
 * @note If `status == 0`, no error occurred. Otherwise, the program exits with
 * an appropriate error message.
 * 
 * @see safe_thread_handle(), error_exit(), t_opcode
 */
static void	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("Невозможно создать поток (лимит).");
	else if (EPERM == status)
		error_exit("Not enought permissions.");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread isnt joinable");
	else if (ESRCH == status)
		error_exit("Cant find thread by that ID.");
	else if (EDEADLK == status)
		error_exit("The deadlock was detected.");
}

/**
 * @brief Safely handles thread operations: create, join, or detach.
 * 
 * Wraps POSIX thread functions (`pthread_create`, `pthread_join`, and
 * `pthread_detach`) and checks for errors via `handle_thread_error`.
 * Allows uniform handling of thread operations through an opcode.
 * 
 * @param thread Pointer to the thread to be created or manipulated.
 * @param foo Thread function (used only with CREATE).
 * @param data Pointer to data passed to the thread function (used 
 * only with CREATE).
 * @param opcode Thread operation to perform: CREATE, JOIN, or DETACH.
 * 
 * @note If an invalid opcode is passed, the program exits with an error.
 * 
 * @see handle_thread_error(), t_opcode
 */
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle");
}
