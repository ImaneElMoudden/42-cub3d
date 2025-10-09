/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:26:50 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 20:39:12 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	invalid_file_content(void)
{
	t_game	*game;

	game = game_data();
	return (!game->input.no_path || !game->input.so_path || !game->input.we_path
		|| !game->input.ea_path || game->input.floor_color == -1
		|| game->input.ceiling_color == -1);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	convert_color(const char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || (r * 10 + (str[i] - 48)) > 255)
			return (exit_error("Input file: Invalid color\n"));
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (r);
}

int	count_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**append_arr(char **arr, char *line, int l)
{
	char	**a;
	int		i;

	a = safe_malloc(sizeof(char *) * (l + 2));
	i = 0;
	while (i < l)
	{
		a[i] = arr[i];
		i++;
	}
	a[i++] = line;
	a[i] = 0;
	return (a);
}
