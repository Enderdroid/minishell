#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	char *b_argv[] = { "echo",
					argv[1],
					NULL };
	int fd[1][2];
	pipe(fd[0]);
	pid_t pid_fork = fork();
	if (!pid_fork)
	{
		// Дочерний процесс
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		execve("/bin/echo", b_argv, envp);
		exit(0);
	}
	wait(0);
		// Родительский процесс
		close(fd[0][1]);
		char buf[1000];
		ssize_t sz;
		sz = read(fd[0][0], buf, sizeof(buf));
		if (sz > 0)
		{
			write(STDOUT_FILENO, buf, sz);
		}
}