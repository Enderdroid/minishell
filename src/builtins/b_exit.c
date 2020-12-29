#include "../../include/libbuiltins.h"
#include "../../include/error.h"

static int	code_extracted(char *s)
{
	long long	nb;
	int			invalid;
	int			sign;

	while (ft_isspace(*s))
		s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	invalid = (ft_isdigit(*s)) ? 0 : 1;
	nb = 0;
	while (ft_isdigit(*s))
	{
		nb = nb * 10 + sign * (*s++ - '0');
		if ((nb != 0) && ((nb > 0) != (sign > 0)))
			invalid = 1;
	}
	while (ft_isspace(*s))
		s++;
	if (invalid || *s)
		return (-1);
	return ((unsigned char)nb);
}

int			b_exit(t_exec *exec)//void?
{
	int code;
	//printf("pid=%i\n", g_data->pid);//
	if (!exec->pipe_from && !exec->pipe_to)
		write(1, "exit\n", 5);
	code = 0;
	if (exec->argv[1])
	{
		if ((code = code_extracted(exec->argv[1])) == -1)
		{
			code = 255;
			error_msg_custom(&exec->ret, "exit", "numeric argument required", 255);
			//(exec->argv[1], "exit", "numeric argument required", 255)
		}
		else if (exec->argv[2])
		{
			code = 1;
			error_msg_custom(&exec->ret, "exit", "too many arguments", 1);
		}
	}
	//printf("code=%i\n", code);//
	if (!(g_data->pid))
		free_and_exit(code);
	return (0);
}
