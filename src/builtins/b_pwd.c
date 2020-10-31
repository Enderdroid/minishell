#include "../../include/libbuiltins.h"

char	*b_pwd()
{
	char	*path;

	path = (char*)malloc(sizeof(char) * PATH_MAX);
	path = getcwd(path, PATH_MAX);
	//IF NULL -> ERROR
	return (path);
}
