/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:37:09 by juhyelee          #+#    #+#             */
/*   Updated: 2023/05/02 16:32:31 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*dup_str(const char *str, const int len);
static char	*join_strs(const char *s1, const char *s2, const int s2_len);
static void	copy_l(char *dst, const char *src, const int d_size);
static int	get_len(const char *str);

char	*marge(char *s1, const char *s2, const int s2_idx)
{
	char	*temp;

	if (s2_idx < 0)
		return (NULL);
	if (s1 == NULL)
		return (dup_str(s2, s2_idx + 1));
	temp = join_strs(s1, s2, s2_idx + 1);
	free(s1);
	return (temp);
}

static char	*dup_str(const char *str, const int len)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (NULL);
	copy_l(temp, str, len + 1);
	return (temp);
}

static char	*join_strs(const char *s1, const char *s2, const int s2_len)
{
	const int	s1_len = get_len(s1);
	char		*temp;

	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (temp == NULL)
		return (NULL);
	copy_l(temp, s1, s1_len + 1);
	copy_l(temp + s1_len, s2, s2_len + 1);
	return (temp);
}

static void	copy_l(char *dst, const char *src, const int d_size)
{
	int	i;

	i = 0;
	while (i < d_size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	get_len(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
