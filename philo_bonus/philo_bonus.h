
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

// init_bonus.c
void	data_init(t_table *table);

// parsing_bonus.c
void	parse_input(t_table *table, char **argv);

// safe_functions_bonus.c
void	*safe_malloc(size_t bytes);
void	safe_sem_handle(sem_t **sem, t_status action);

// utils_bonus.c
long	gettime(t_time_code time_code);
#endif