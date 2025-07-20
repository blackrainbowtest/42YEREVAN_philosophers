/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:24:45 by root              #+#    #+#             */
/*   Updated: 2025/07/20 16:20:47 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_BONUS_H
# define DEFS_BONUS_H

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
	TAKE_FORK,
	DIED,
}	t_status;

typedef enum e_opcode
{
	CREATE,
	WAIT,
	POST,
	CLOSE,
	UNLINK,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

# define FORKS "/forks"
# define LOCK "/write_lock"
# define CHECK "/meal_check"
# define FINISH "/finish"
# define SYNCLOCK "/sync_lock"

#endif