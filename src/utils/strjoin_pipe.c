#include "../../include/libincludes.h"
#include "../../include/libbuiltins.h"

char *ft_pipe_strjoin(char const *s1, char const *s2)
{
	char *new;
	char *newptr;
	size_t s1_len;

	if (!s2)
		return (NULL);
	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	newptr = new;
	if (s1)
		while (*s1)
			*newptr++ = *s1++;
	while (*s2)
		*newptr++ = *s2++;
	*newptr = '\0';
	return (new);
}
