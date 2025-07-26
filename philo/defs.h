/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:24:45 by root              #+#    #+#             */
/*   Updated: 2025/07/13 01:27:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// Colors
# define RST "\033[0m"
# define RED "\033[1;31m"
# define G   "\033[1;32m"
# define Y   "\033[1;33m"
# define B   "\033[1;34m"
# define M   "\033[1;35m"
# define C   "\033[1;36m"
# define W   "\033[1;37m"

// Debug
# define DEBUG_MODE 0

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

#endif