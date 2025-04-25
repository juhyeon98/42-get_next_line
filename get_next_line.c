#include "get_next_line.h"

static int	is_not_contain_nl(const char *str);
static char	*merge(char *s1, const char *s2);
static char	*dup_str(const char *str, const char sp_char);
static void	org_remain(char **remain);

char	*get_next_line(int fd)
{
	static t_fd	*fds;
	t_fd		*curr;
	char		*ret;
	char		buffer[BUFFER_SIZE + 1];
	int			len;

	curr = find_fd(fds, fd);
	if (!curr)
		curr = add_fd(&fds, fd);
	if (!curr)
		return (NULL);
	while (is_not_contain_nl(curr->remain))
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len <= 0)
			break ;
		buffer[len] = '\0';
		curr->remain = merge(curr->remain, buffer);
	}
	ret = dup_str(curr->remain, '\n');
	org_remain(&(curr->remain));
	remove_fd(&fds, curr);
	return (ret);
}

static int	is_not_contain_nl(const char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}

static char	*merge(char *s1, const char *s2)
{
	const size_t	s1_len = get_len(s1, '\0');
	const size_t	s2_len = get_len(s2, '\0');
	char	*ret;

	if (!*s2)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!ret)
		return (NULL);
	copy_str(ret, s1, s1_len + 1);
	copy_str(ret + s1_len, s2, s2_len + 1);
	if (s1)
		free(s1);
	s1 = NULL;
	return (ret);
}

static char	*dup_str(const char *str, const char sp_char)
{
	const size_t	size = get_len(str, sp_char) + 1;
	char			*ret;

	if (!str)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	copy_str(ret, str, size);
	return (ret);
}

static void	org_remain(char **remain)
{
	const size_t	nl_len = get_len(*remain, '\n');
	const size_t	end_len = get_len(*remain, '\0');
	const size_t	size = end_len - nl_len + 1;
	char			*ret;

	if (!*remain)
		return ;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return ;
	copy_str(ret, *remain + nl_len, size);
	free(*remain);
	*remain = dup_str(ret + 1, '\0');
	free(ret);
	if (!(*remain)[0])
	{
		free(*remain);
		*remain = NULL;
	}
}
