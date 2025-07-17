#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
// #include <sched.h>


/**
 * wait(&status) — ждёт любого ребёнка.
 *
 * WIFEXITED(status) — проверяет, завершился ли нормально.
 *
 * WEXITSTATUS(status) — возвращает код выхода из exit().
 */
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