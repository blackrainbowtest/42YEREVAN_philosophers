#include "philo_bonus.h"

void	cleanup_semaphores(void)
{
	sem_unlink(SEM_DIE);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_WRITE);
}