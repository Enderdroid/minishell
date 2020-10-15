#ifndef LIBUTILS_H
# define LIBUTILS_H

# include "libincludes.h"

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_dellchar(char *s, char *i);
void				*ft_memset(void *destination, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t num, size_t size);
char				*ft_strdup(const char *str);

#endif
