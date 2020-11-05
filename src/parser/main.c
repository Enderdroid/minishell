#include "../../include/parser.h"

int	main(int ac, char **av, char** envp)
{
	char	*line;
	int		i;
	int		size;

	g_code = 0;
	(void)ac;
	(void)av;
	env = parse_env(envp, &size);
	t_u_env path_env = parse_u_env(env, size);
	parse_input(env);
	/*	char *x = ft_strdup("\"ds\"$TH\\b");
		char *n= ft_strdup("011021101");
		correct_str(&x, 9, n);
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
