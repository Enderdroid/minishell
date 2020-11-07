#include "../../include/parser.h"

int	main(int ac, char **av, char** envp)
{
	(void)ac;
	(void)av;

	init_data(envp);
	parse_input();
	/*	char *x = ft_strdup("\"jj\"");
		char *n= ft_strdup("0110");
		int len = 4;
		correct_str(&x, &len, &n);
		printf("%s\n", x);*/

	//char *str = "c   ;";
	//input_is_valid(str);
	/*
	i = -1;
	while (++i < size)
	{
		printf("%s\n", (env[i]).key);
		printf("%s\n", (env[i]).value);
		printf("%s\n", *((env[i]).link));
	}
	printf("%s\n", (path_env.l_old_pwd->key));
	printf("%s\n", (path_env.l_old_pwd->value));
	printf("%s\n", (path_env.l_pwd->key));
	printf("%s\n", (path_env.l_pwd->value));
	printf("%s\n", *(path_env.path_content));
	*/
}
