#include <stdio.h>

int main(int argc, char const *argv[], char **env)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		++i;
	}
	return 0;
}
