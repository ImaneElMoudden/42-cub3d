/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:54 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_file(char *file)
{
	t_game	*game;
	int		fd;
	char	*line;

	game = game_data();
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write_error("Input file: Cannot open file\n"));
	game->input.input_fd = fd;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
			continue ;
		if (parse_line(line, fd))
			return (1);
	}
	if (validate_map())
		return (1);
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac != 2)
		return (write_error("Invalid number of arguments\n"));
	if (ft_strlen(av[1]) <= 4 || ft_strncmp(&av[1][ft_strlen(av[1]) - 4],
		".cub", 4))
		return (write_error("Invalid input file format\n"));
	return (0);
}
