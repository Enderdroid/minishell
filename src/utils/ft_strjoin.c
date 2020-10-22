#include "../include/libutils.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	r_size;
	size_t	i;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	r_size = s_len + d_len;
	if (d_len >= size)
		r_size = s_len + size;
	while (src[i] != '\0' && d_len + 1 < size)
		dst[d_len++] = src[i++];
	if (i)
		dst[d_len] = '\0';
	return (r_size);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		f_len;
	size_t		s_len;
	char		*str_j;

	if (!s1 || !s2)
		return (NULL);
	f_len = ft_strlen(s1);
	s_len = ft_strlen(s2);
	str_j = ft_calloc(f_len + s_len + 1, sizeof(char));
	if (str_j == NULL)
		return (NULL);
	ft_strlcat(str_j, s1, f_len + s_len + 1);
	ft_strlcat(str_j, s2, f_len + s_len + 1);
	return (str_j);
}
