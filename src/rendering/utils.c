/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:01:16 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/03 16:57:24 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(t_game *game, t_dda *dda)
{
	if (dda->map.x < 0 || dda->map.x >= (int)game->map.width
		|| dda->map.y < 0 || dda->map.y >= (int)game->map.height)
		return (1);
	if (game->map.grid[dda->map.y][dda->map.x] == '1')
		return (1);
	return (0);
}

double	apply_fisheye_correction(t_game *game, t_dda *dda, double dist)
{
	double	proj_cos;

	proj_cos = game->player.dir.x * dda->rdir.x
		+ game->player.dir.y * dda->rdir.y;
	if (proj_cos != 0)
		dist /= proj_cos;
	if (dist < 0.0001)
		dist = 0.0001;
	return (dist);
}

int	is_door_tile(char c)
{
	return (c == 'H' || c == 'V');
}
