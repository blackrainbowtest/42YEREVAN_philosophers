/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:24:45 by root              #+#    #+#             */
/*   Updated: 2025/07/16 20:20:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>			//|printf
# include <stdlib.h>		//|malloc, free
# include <unistd.h>		//|usleep
# include <stdbool.h>		//|bool (true/false)
# include <pthread.h>		//|mutex: init, lock, unlock, destroy
							//|thread: create, join, detach
# include <sys/time.h>		//|gettimeofday
# include <limits.h>		//|INT_MAX
# include <errno.h>			//|EAGAIN, EPERM, EINVAL, ESRCH, EDEADLK, ENOMEM
							//|EBUSY

# include "defs.h"
# include "types.h"

// ========== parsing.c ==========
void	parse_input(t_table *table, char **argv);

// ========== utils.c ==========
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);

// ========== safe.c ==========
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

// ========== init.c ==========
void	data_init(t_table *table);

// ========== syncro_utils.c ==========
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finish(t_table *table);
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	de_synchronize_philos(t_philo *philo);

// ========== dinner.c ==========
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);
void	*lone_philo(void *arg);
void	*dinner_simulation(void *data);

// ========== monitor.c ==========
void	monitor_dinner(void *data);
bool	philo_died(t_philo *philo);

// ========== write.c ==========
void	write_status(t_status status, t_philo *philo, bool debug);

#endif