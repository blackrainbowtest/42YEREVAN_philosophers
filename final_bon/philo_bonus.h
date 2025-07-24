/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:40:52 by root              #+#    #+#             */
/*   Updated: 2025/07/24 08:43:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
#include <signal.h>

# include "defs_bonus.h"
# include "types_bonus.h"

/*====dinner_bonus.c====*/
void	dinner_start(t_table *table);

/*====getters_setters_bonus.c====*/
void	set_bool(sem_t **sem, bool *dest, bool value);
bool	get_bool(sem_t **sem, bool *value);
void	set_long(sem_t **sem, long *dest, long value);
long	get_long(sem_t **sem, long *value);
bool	simulation_finish(t_table *table);

/*====init_bonus.c====*/
void	data_init(t_table *p_table);

/*====monitor_bonus.c====*/
void	start_monitors(t_table *table);

/*====parse_bonus.c====*/
void	parse_input(t_table *p_table, char **argv);

/*====utils_clean_bonus.c====*/
void	cleanup_semaphores(void);
void	error_exit(const char *error);
void	clean_exit(t_table *table, const char *msg, bool is_parent, int exit_code);

/*====utils_safe_bonus.c====*/
void	*safe_malloc(size_t bytes);
void	safe_sem_handle(sem_t **sem, t_opcode opcode);

/*====utils_time_bonus.c====*/
long	get_time(t_table *p_table, t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

/*====write_bonus.c====*/
void	write_status(t_status status, t_philo *philo, bool debug);

#endif	/* PHILO_BONUS_H */