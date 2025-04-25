#include "get_next_line.h"

t_fd	*find_fd(const t_fd *list, const int fd)
{
	t_fd	*curr;

	curr = (t_fd *)list;
	while (curr)
	{
		if (curr->fd == fd)
			break ;
		curr = curr->next;
	}
	return (&curr);
}

t_fd	*add_fd(t_fd **list, const int fd)
{
	t_fd	*new_fd;

	new_fd = (t_fd *)malloc(sizeof(t_fd));
	if (!new_fd)
		return (NULL);
	new_fd->fd = fd;
	new_fd->remain = NULL;
	new_fd->next = NULL;
	if (*list)
	{
		new_fd->next = *list;
	}
	*list = new_fd;
	return (new_fd);
}

void	remove_fd(t_fd **list, t_fd *node)
{
	t_fd	*prev;

	if (*list == node)
	{
		*list = (*list)->next;
	}
	else
	{
		prev = *list;
		while (prev->next != node)
			prev = prev->next;
		prev->next = node->next;
	}
	if (node->remain)
		free(node->remain);
	free(node);
}

void	copy_str(char *dst, const char *org, const size_t o_size)
{
	size_t	index;

	if (!org)
		return ;
	index = 0;
	while (org[index] && index + 1 < o_size)
	{
		dst[index] = org[index];
		index++;
	}
	dst[index] = '\0';
}

size_t	get_len(const char *str, const char sp_char)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
	{
		if (str[len] == sp_char)
			break ;
		len++;
	}
	return (len);
}
