
#include "../../include/parser.h"
#include <fcntl.h>

static int	process_rdr_left(t_exec *exec, char *filename)
{
	if (exec->fd_new[0] > 1)
		close(exec->fd_new[0]);
	exec->fd_new[0] = open(filename, O_RDONLY);
	if (exec->fd_new[0] < 0)
	{
		g_code = 1;
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		free_exec(exec);
		exec = NULL;
		return (0);
	}
	return (1);
}

static void	process_rdr_right(t_exec *exec, char *filename, int cmd) //void or int?
{
	if (exec->fd_new[1] > 1)
		close(exec->fd_new[1]);
	if (cmd == C_RDR_R_DBL)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_APPEND, S_IRWXU | S_IROTH);
	if (cmd == C_RDR_R)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_APPEND, S_IRWXU | S_IROTH);
	//if (exec->fd_new[0] < 0)?
}

int			process_rdr(t_dlist **lst, t_exec *exec, t_dlist **lptr, char **argv)
{
	char	*filename;
	int		cmd;

	cmd = ((t_token *)((*lptr)->content))->len;
	*lptr = (*lptr)->next;
	filename = ((t_token *)((*lptr)->content))->str;
	printf("%s\n", filename);
	if (cmd == C_RDR_L)
	{
		if (!process_rdr_left(exec, filename))
			return (0);
	}
	else
		process_rdr_right(exec, filename, cmd);
	if (!exec->name && (*lptr)->next)
	{
		*lptr = (*lptr)->next;
		fill_name_path(((t_token *)((*lptr)->content))->str, exec, &argv[0], lst);
	}
	return (1);
}

