#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	check(void)
{
	system("leaks a.out");
}

int	main(void)
{
	char	*ret;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while (1)
	{
		ret = get_next_line(fd);
		if (!ret)
			break ;
		puts(ret);
		free(ret);
		usleep(100);
	}
	close(fd);
	atexit(check);
	return (0);
}
