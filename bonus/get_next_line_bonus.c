/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:08:27 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 22:39:49 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static char	*read_to_newline(int fd, char *remain)
{
	char	*buf;
	ssize_t	bytes;
	char	*tmp;

	buf = safe_malloc(BUFFER_SIZE + 1);
	bytes = 1;
	while (!ft_strchr(remain, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (NULL);
		buf[bytes] = '\0';
		tmp = safe_strjoin(remain, buf);
		remain = tmp;
	}
	return (remain);
}

static char	*extract_line(char *remain)
{
	int		i;
	char	*line;

	if (!remain || !*remain)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (remain[i] == '\n')
		i++;
	line = safe_substr(remain, 0, i);
	return (line);
}

static char	*update_remain(char *remain)
{
	int		i;
	char	*new_remain;

	if (!remain)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
		return (NULL);
	new_remain = safe_strdup(remain + i + 1);
	return (new_remain);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	int			len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain)
		remain = safe_strdup("");
	remain = read_to_newline(fd, remain);
	if (!remain)
		return (NULL);
	line = extract_line(remain);
	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	remain = update_remain(remain);
	return (safe_substr(line, 0, ft_strlen(line)));
}
