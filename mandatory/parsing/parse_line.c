/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:15:22 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:15:25 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	assign_path(char **id, char *line)
{
	int	c;

	while (*line && ft_isspace(*line))
		line++;
	c = 0;
	while (line[c] && !ft_isspace(*line))
		c++;
	if (!c)
		return (write_error("Input file: Invalid texture path\n"));
	*id = safe_substr(line, 0, c);
	return (0);
}

static int	assign_color(int *id, char *line)
{
	char	**arr;
	int		a[3];
	int		i;

	while (*line && ft_isspace(*line))
		line++;
	arr = ft_split(line, ',');
	if (count_array(arr) != 3)
		return (write_error("Input file: Invalid color\n"));
	i = 0;
	while (i < 3)
	{
		if (!is_numeric(arr[i]))
			return (write_error("Input file: Invalid color\n"));
		a[i] = ft_atoi(arr[i]);
		if (a[i] < 0 || a[i] > 255)
			return (write_error("Input file: Invalid color\n"));
		i++;
	}
	*id = create_rgb(a[0], a[1], a[2]);
	return (0);
}
// handle atoi overflow

static int	parse_id(char *line)
{
	t_game	*game;

	game = game_data();
	if (!ft_strncmp(line, "NO ", 3) && !game->input.no_path)
		return (assign_path(&game->input.no_path, line + 3));
	if (!ft_strncmp(line, "SO ", 3) && !game->input.so_path)
		return (assign_path(&game->input.so_path, line + 3));
	if (!ft_strncmp(line, "WE ", 3) && !game->input.we_path)
		return (assign_path(&game->input.we_path, line + 3));
	if (!ft_strncmp(line, "EA ", 3) && !game->input.ea_path)
		return (assign_path(&game->input.ea_path, line + 3));
	if (!ft_strncmp(line, "F ", 2) && game->input.floor_color == -1)
		return (assign_color(&game->input.floor_color, line + 2));
	if (!ft_strncmp(line, "C ", 2) && game->input.ceiling_color == -1)
		return (assign_color(&game->input.ceiling_color, line + 2));
	return (write_error("Input file: Duplicated content\n"));
}

static int	parse_map(char *line, int fd)
{
	t_game	*game;
	int		i;
	char	**map;

	if (invalid_file_content())
		return (write_error("Input file: Invalid content\n"));
	game = game_data();
	i = 1;
	map = safe_malloc(sizeof(char *) * (i + 1));
	map[0] = line;
	map[1] = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
			return (write_error("Invalid map\n"));
		map = append_arr(map, line, i);
		i++;
	}
	game->map.map = map;
	return (0);
}

int	parse_line(char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
		{
			if (!ft_strncmp(&line[i], "NO ", 3) || !ft_strncmp(&line[i], "SO ",
					3) || !ft_strncmp(&line[i], "WE ", 3)
				|| !ft_strncmp(&line[i], "EA ", 3) || !ft_strncmp(&line[i],
					"F ", 2) || !ft_strncmp(&line[i], "C ", 2))
				return (parse_id(&line[i]));
			else
				return (parse_map(line, fd));
		}
		i++;
	}
	return (0);
}
