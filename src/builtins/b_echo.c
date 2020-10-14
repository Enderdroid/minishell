#include "../../include/libbuiltins.h"
#include "../../include/libutils.h"

ssize_t	b_echo(char *str, int fd, int flag)
{
	ssize_t m_ret;
	ssize_t n_ret;

	n_ret = 0;
	m_ret = write(fd, str, ft_strlen(str));
	//IF m_ret == -1 -> ERROR
	if (flag)
		n_ret = write(fd, "\n", 1);
	//IF n_ret == -1 -> ERROR
	return (m_ret + n_ret);
}
