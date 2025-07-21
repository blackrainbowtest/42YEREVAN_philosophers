#include "philo_bonus.h"

static inline bool	any_semaphore_failed_to_open(t_sem *sem)
{
	return (sem->die_sem == SEM_FAILED || sem->fork_sem == SEM_FAILED
			|| sem->meal_sem == SEM_FAILED || sem->write_sem == SEM_FAILED);
}

static inline bool	any_semaphore_failed_to_unlink(void)
{
	return (sem_unlink(DIE) == -1 || sem_unlink(FORK) == -1
		|| sem_unlink(MEAL) == -1 || sem_unlink(WRITE) == -1);
}

static void	init_philosophers(t_table *p_table)
{
	//TODO
}

static void	init_semaphores(t_table *p_table)
{
	t_sem	*sem;

	cleanup_semaphores();
	sem = (t_sem *)safe_malloc(sizeof(t_sem));
	memset(sem, 0, sizeof(t_sem));
	sem->die_sem = sem_open(SEM_DIE, O_CREAT | O_EXCL, 0644, 1);
	sem->fork_sem = sem_open(SEM_FORK, O_CREAT | O_EXCL, 0644, p_table->philo_count);
	sem->meal_sem = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 0);
	sem->write_sem = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	if (any_semaphore_failed_to_open(sem))
		clean_exit(p_table, "Semaphore "RED"OPEN"RST" Error\n", true, EXIT_FAILURE);
	if (any_semaphore_failed_to_unlink())
		clean_exit(p_table, "Semaphore "RED"UNLINK"RST" Error\n", true, EXIT_FAILURE);
	p_table->sem = sem;
}

void	data_init(t_table *p_table)
{
	init_semaphores(p_table);
	init_philosophers(p_table);//TODO
}
