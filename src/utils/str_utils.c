#include "../../include/libutils.h"

size_t				ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s_size;
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	s_size = ft_strlen(src);
	if (size == 0)
		return (s_size);
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (s_size);
}

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
