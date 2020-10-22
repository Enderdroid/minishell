#include <stdio.h>

int main(int argc, char const *argv[], char **env)
{
	int i;
	i = 0;
	while (env[i])
	{
		printf("%s", env[i]);
		printf("\n");
		++i;
	}

	return 0;
}
