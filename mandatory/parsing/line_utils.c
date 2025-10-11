/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:14:44 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/10 14:46:22 by ielmoudd         ###   ########.fr       */
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

int	write_error(char *str)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	write(2, str, ft_strlen(str));
	return (1);
}

int	exit_error(char *str)
{
	write_error(str);
	clean((void *)1);
	return (1);
}
