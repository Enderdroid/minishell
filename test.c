#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_MAX 1024

int main(int argc,  char *argv[], char *envp[])
{
	int i = 0;

	while (envp[i])
	{
		printf ("%s\n", envp[i]);
		++i;
	}
	
	return 0;
}
