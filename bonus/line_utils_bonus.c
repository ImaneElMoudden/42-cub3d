/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:11:59 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 20:37:49 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
