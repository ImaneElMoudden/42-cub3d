/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_borders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:15:05 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:15:08 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_walkable_tile(char c)
{
	return (c == '0' || c == 'd' || c == 'D');
}

static int	check_corners(int y, int x, int len)
{
	t_map	*map;

	map = &game_data()->map;
	if (y - 1 < 0 || x >= ft_strlen(map->map[y - 1]) || map->map[y
			- 1][x] == ' ')
		return (1);
	if (y + 1 >= map->map_height || x >= ft_strlen(map->map[y + 1])
		|| map->map[y + 1][x] == ' ')
		return (1);
	if (x - 1 < 0 || map->map[y][x - 1] == ' ')
		return (1);
	if (x + 1 >= len || map->map[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	check_map_boundaries(void)
{
	int		y;
	int		x;
	int		len;
	t_map	*map;

	y = 0;
	map = &game_data()->map;
	while (y < map->map_height)
	{
		len = ft_strlen(map->map[y]);
		x = 0;
		while (map->map[y][x])
		{
			if (is_walkable_tile(map->map[y][x]) && check_corners(y, x, len))
				return (write_error("Map: map must be surrounded by walls\n"));
			x++;
		}
		y++;
	}
	return (0);
}

int	finalize_map(void)
{
	t_map	*map;
	char	**arr;
	int		i;
	int		j;
	int		len;

	map = &game_data()->map;
	arr = safe_malloc(sizeof(char *) * (map->map_height + 1));
	i = 0;
	while (i < map->map_height)
	{
		arr[i] = safe_malloc(map->map_width + 1);
		len = ft_strlen(map->map[i]);
		j = (int)ft_strlcpy(arr[i], map->map[i], map->map_width + 1);
		while (j < map->map_width)
			arr[i][j++] = ' ';
		arr[i][j] = 0;
		i++;
	}
	arr[i] = 0;
	map->map = arr;
	return (0);
}
