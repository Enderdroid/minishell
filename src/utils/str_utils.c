#include "../../include/libincludes.h"

//Переписать на возможность удаления (n >= 1) значных индексов
int					ft_dellchar(char *s, char *i)
{
	size_t	s_ind;
	size_t	ind;

	ind = 0;
	while (i[ind])
	{
		s_ind = i[ind] - '0';
		while (s[s_ind])
			s[s_ind] = s[s_ind + 1];
		++ind;
	}
	return (--ind);
}
