/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:33:23 by juhyelee          #+#    #+#             */
/*   Updated: 2023/05/02 16:33:55 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	is_full_buffer(t_buffer *buffer, const int fd);
static char	*get_line(char *re, t_buffer *buffer, const int l_idx);
static char	*return_line(char *re, int is_full);

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	char			*re;
	int				i;
	int				is_full;

	re = NULL;
	i = 0;
	is_full = 1;
	if (buffer.len == 0)
		is_full = is_full_buffer(&buffer, fd);
	while (is_full == 1)
	{
		if (buffer.buffer[i] == '\n')
			return (get_line(re, &buffer, i));
		else if (i == buffer.len)
		{
			re = marge(re, buffer.buffer, i - 1);
			buffer.len = 0;
			is_full = is_full_buffer(&buffer, fd);
			i = 0;
		}
		else
			i++;
	}
	return (return_line(re, is_full));
}

static int	is_full_buffer(t_buffer *buffer, const int fd)
{
	buffer->len = read(fd, buffer->buffer, BUFFER_SIZE);
	if (buffer->len > 0)
		buffer->buffer[buffer->len] = '\0';
	if (buffer->len < 0)
	{
		buffer->buffer[0] = 0;
		buffer->len = 0;
		return (-1);
	}
	else if (buffer->len == 0)
		return (0);
	return (1);
}

static char	*get_line(char *re, t_buffer *buffer, const int l_idx)
{
	char	*temp;
	int		i;

	temp = marge(re, buffer->buffer, l_idx);
	i = 0;
	while (i + l_idx + 1 < buffer->len)
	{
		buffer->buffer[i] = buffer->buffer[i + l_idx + 1];
		i++;
	}
	buffer->buffer[i] = '\0';
	buffer->len = i;
	return (temp);
}

static char	*return_line(char *re, int is_full)
{
	if (is_full == -1)
	{
		if (re != NULL)
			free(re);
		return (NULL);
	}
	return (re);
}
