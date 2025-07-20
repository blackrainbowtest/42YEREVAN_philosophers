
#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>

# include <sys/wait.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

#include "defs_bonus.h"
#include "types_bonus.h"

//TODO

// clean_bonus.c
void	cleanup_semaphores(void);
void	clean(t_table *table);

// dinner_bonus.c
void	dinner_start(t_table *table);

// error_bonus.c
void	error_exit(const char *error);

// getters_setters.c
void	set_bool(sem_t **sem, bool *dest, bool value);
bool	get_bool(sem_t **sem, bool *value);
void	set_long(sem_t **sem, long *dest, long value);
long	get_long(sem_t **sem, long *value);
bool	simulation_finish(t_table *table);

// init_bonus.c
void	data_init(t_table *table);

// parsing_bonus.c
void	parse_input(t_table *table, char **argv);

// safe_functions_bonus.c
void	*safe_malloc(size_t bytes);
void	safe_sem_handle(sem_t **sem, t_opcode opcode);
sem_t	*safe_sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
void	safe_sem_unlink(const char *name);

// utils_bonus.c
long	gettime(t_time_code time_code);

// write_bonus.c
void	write_status(t_status status, t_philo *philo, bool debug);
#endif