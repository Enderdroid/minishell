#include "../../include/libstruct.h"
#include "../../include/error.h"

int		error_msg_auto(char *filename, int code)
{
	g_data->code = code;
	error_msg_prompt(filename);
	ft_putendl_fd(strerror(errno), 1);
	return (0);
}

int		error_msg_custom(char *filename, char *message, int code)
{
	g_data->code = code;
	error_msg_prompt(filename);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (0);
}

void	error_msg_prompt(char *filename)
{
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
}

