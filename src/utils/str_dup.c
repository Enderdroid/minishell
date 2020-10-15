#include "../../include/libutils.h"

void		*ft_memset(void *destination, int c, size_t n)
{
	char	*dst;
	size_t	i;

	dst = destination;
	i = 0;
	while (i < n)
	{
		dst[i] = c;
		++i;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void		*ft_calloc(size_t num, size_t size)
{
	void	*alloc;

	alloc = malloc(num * size);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, num * size);
	return (alloc);
}

char		*ft_strdup(const char *str)
{
	char	*alloc;
	size_t	size;

	size = ft_strlen(str);
	alloc = ft_calloc(size + 1, sizeof(char));
	if (alloc == NULL)
		return (NULL);
	ft_strlcpy(alloc, str, size + 1);
	return (alloc);
}
