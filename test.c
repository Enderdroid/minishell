#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX 1024

int main(int argc,  char *argv[], char *envp[])
{
	char c_path_buf[PATH_MAX];

	getcwd(c_path_buf, PATH_MAX);
	printf("%s\n", c_path_buf);
	int ret = chdir("./jhfgjkfdhkj");
	getcwd(c_path_buf, PATH_MAX);
	printf("%s\n", c_path_buf);
	printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	printf("%i\n", ret);
	return 0;
}
