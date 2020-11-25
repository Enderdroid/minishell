#include "../../include/libbuiltins.h"

ssize_t	b_echo(char **str, int fd)
{
	ssize_t m_ret;
	ssize_t n_ret;
	int ind;
	int flag;

	flag = 1;
	ind = 1;
	n_ret = 0;
	if (ft_strcmp(str[1], "-n"))
	{
		ind = 0;
		flag = 0;
	}
	while (str[++ind] && m_ret > 0)
		m_ret = write(fd, str[ind], ft_strlen(str[ind]));
	//IF m_ret == -1 -> ERROR
	if (flag)
		n_ret = write(fd, "\n", 1);
	//IF n_ret == -1 -> ERROR
	return (m_ret + n_ret);
}
