/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:14:08 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:14:09 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*read_to_newline(int fd, char *remain)
{
	char	*buf;
	ssize_t	bytes;
	char	*tmp;

	buf = safe_malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
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
	static char	*remain[1024];
	char		*line;
	int			len;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remain[fd])
		remain[fd] = safe_strdup("");
	remain[fd] = read_to_newline(fd, remain[fd]);
	if (!remain[fd])
		return (NULL);
	line = extract_line(remain[fd]);
	if (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}
	remain[fd] = update_remain(remain[fd]);
	return (safe_substr(line, 0, ft_strlen(line)));
}
