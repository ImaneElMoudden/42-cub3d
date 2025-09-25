/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:26:50 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -s;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (s * r);
}
// atoi needs to change to handle overflow

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
