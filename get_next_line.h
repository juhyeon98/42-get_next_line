#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct s_fd
{
	int			fd;
	char		*remain;
	struct s_fd	*next;
}t_fd;

char	*get_next_line(int fd);
t_fd	*find_fd(const t_fd *list, const int fd);
t_fd	*add_fd(t_fd **list, const int fd);
void	remove_fd(t_fd **list, t_fd *node);
void	copy_str(char *dst, const char *org, const size_t o_size);
size_t	get_len(const char *str, const char sp_char);

#endif
