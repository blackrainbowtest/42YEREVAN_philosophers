#include <unistd.h>
#include <stdio.h>
// #include <sched.h>

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