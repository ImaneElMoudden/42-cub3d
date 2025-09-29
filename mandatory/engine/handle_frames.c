/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frames.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:11:15 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 15:11:16 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	frames_handler(void)
{
	t_time			*time;

	time = &game_data()->time;
	time->now = get_time_in_seconds();
	time->elapsed = time->now - time->last_time;
	if (time->elapsed < time->target)
	{
		usleep((useconds_t)((time->target - time->elapsed) * 1000000.0));
		time->now = get_time_in_seconds();
		time->elapsed = time->now - time->last_time;
	}
	time->delta_time = time->elapsed;
	time->last_time = time->now;
}
