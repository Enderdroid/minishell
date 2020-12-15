#include "../../include/libbuiltins.h"

int	b_exit(void)
{
	if (!(g_data->pid))
		free_and_exit(0);
	return (0);
}