/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:31:21 by juhyelee          #+#    #+#             */
/*   Updated: 2023/05/02 16:32:54 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define END_OF_FILE -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE + 1];
	int		len;
}	t_buffer;

char	*marge(char *s1, const char *s2, const int s2_idx);
char	*get_next_line(int fd);

#endif
