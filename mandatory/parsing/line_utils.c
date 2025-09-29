/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:14:44 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:14:45 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isspace(char c)
{
	return (c == 32);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line && !ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_numeric(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	write_error(char *str)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	write(2, str, ft_strlen(str));
	return (1);
}
