/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_safe_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:32:13 by root              #+#    #+#             */
/*   Updated: 2025/07/22 00:32:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*safe_malloc(size_t bytes)
{
	void	*p_ret;

	p_ret = malloc(bytes);
	if (NULL == p_ret)
		error_exit("Error with the malloc");
	return (p_ret);
}

static void	handle_sem_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == -1)
	{
		if (errno == EINVAL && (WAIT == opcode || POST == opcode))
			error_exit("Semaphore is not valid or not initialized.");
		else if (errno == EINVAL && CREATE == opcode)
			error_exit("Semaphore attribute or name is invalid.");
		else if (errno == EINTR && WAIT == opcode)
			error_exit("Semaphore wait was interrupted by a signal.");
		else if (errno == EACCES)
			error_exit("Permission denied to access the semaphore.");
		else if (errno == EOVERFLOW)
			error_exit("Semaphore value exceeds SEM_VALUE_MAX.");
		else
			error_exit("Unexpected semaphore error.");
	}
}

void	safe_sem_handle(sem_t **sem, t_opcode opcode)
{
	if (WAIT == opcode)
		handle_sem_error(sem_wait(*sem), opcode);
	else if (POST == opcode)
		handle_sem_error(sem_post(*sem), opcode);
	else if (CLOSE == opcode)
		handle_sem_error(sem_close(*sem), opcode);
	else
		error_exit("safe_sem_handle: unknown opcode");
}
