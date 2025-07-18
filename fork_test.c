#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(void)
{
	sem_t	sem;
	pid_t	pid;

	// 1 — для межпроцессного использования, 1 — начальное значение
	sem_init(&sem, 1, 1);
	pid = fork();
	if (pid == 0)
	{
		sem_wait(&sem);
		printf("Child enter in critical section\n");
		sleep(2);
		printf("Child exit\n");
		sem_post(&sem);
		exit(0);
	}
	else
	{
		sem_wait(&sem);
		printf("Parent enter in critical section\n");
		sleep(2);
		printf("Parent exit\n");
		sem_post(&sem);
		wait(NULL);
		sem_destroy(&sem);
	}
	return (0);
}

/**
 * wait(&status) — ждёт любого ребёнка.
 *
 * WIFEXITED(status) — проверяет, завершился ли нормально.
 *
 * WEXITSTATUS(status) — возвращает код выхода из exit().
 */
/**
int	main(void)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		printf("Child: work 2 seconds ...\n");
		sleep(2);
		printf("Child: ending process\n");
		exit(42);
	}
	else
	{
		int status;
		wait(&status);
		printf("Parent: child end his work\n");
		if (WIFEXITED(status))
			printf("Child exit code: %d\n", WEXITSTATUS(status));
	}
	return (0);
}
*/

/**
 * fork() запускает копию текущего процесса.
 * В родителе fork() возвращает PID дочернего процесса.
 * В дочернем — возвращает 0.
 * Если ошибка — возвращает -1.
 */
/**
int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
		printf("Я — дочерний процесс. PID: %d\n", getpid());
	else
		printf("Я — родитель. Мой PID: %d. PID ребёнка: %d\n", getpid(), pid);
	
	return (0);
}
 */