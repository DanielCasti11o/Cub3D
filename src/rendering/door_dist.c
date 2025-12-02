/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:17:21 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/01 20:35:56 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calc_door_dist_v(t_game *game, t_dda *dda)
{
	double	door_pos;
	double	dist;
	double	hit_y;

	if (fabs(dda->rdir.x) < 1e-6)
		return (-1);
	if (dda->rdir.x > 0)
		door_pos = 0.5 - DOOR_THICK / 2;
	else
		door_pos = 0.5 + DOOR_THICK / 2;
	dist = (dda->door_map.x + door_pos - game->player.pos.x) / dda->rdir.x;
	if (dist < 0)
		return (-1);
	hit_y = game->player.pos.y + dist * dda->rdir.y;
	if (hit_y < dda->door_map.y || hit_y > dda->door_map.y + 1)
		return (-1);
	return (apply_fisheye_correction(game, dda, dist));
}

static double	calc_door_dist_h(t_game *game, t_dda *dda)
{
	double	door_pos;
	double	dist;
	double	hit_x;

	if (fabs(dda->rdir.y) < 1e-6)
		return (-1);
	if (dda->rdir.y > 0)
		door_pos = 0.5 - DOOR_THICK / 2;
	else
		door_pos = 0.5 + DOOR_THICK / 2;
	dist = (dda->door_map.y + door_pos - game->player.pos.y) / dda->rdir.y;
	if (dist < 0)
		return (-1);
	hit_x = game->player.pos.x + dist * dda->rdir.x;
	if (hit_x < dda->door_map.x || hit_x > dda->door_map.x + 1)
		return (-1);
	return (apply_fisheye_correction(game, dda, dist));
}

static double	calc_side_dist_v(t_game *game, t_dda *dda)
{
	double	side_pos;
	double	dist;
	double	hit_x;

	if (fabs(dda->rdir.y) < 1e-6)
		return (-1);
	if (dda->rdir.y > 0)
		side_pos = dda->door_map.y;
	else
		side_pos = dda->door_map.y + 1;
	dist = (side_pos - game->player.pos.y) / dda->rdir.y;
	if (dist < 0)
		return (-1);
	hit_x = game->player.pos.x + dist * dda->rdir.x;
	if (hit_x < dda->door_map.x + 0.5 - DOOR_THICK / 2)
		return (-1);
	if (hit_x > dda->door_map.x + 0.5 + DOOR_THICK / 2)
		return (-1);
	return (apply_fisheye_correction(game, dda, dist));
}

static double	calc_side_dist_h(t_game *game, t_dda *dda)
{
	double	side_pos;
	double	dist;
	double	hit_y;

	if (fabs(dda->rdir.x) < 1e-6)
		return (-1);
	if (dda->rdir.x > 0)
		side_pos = dda->door_map.x;
	else
		side_pos = dda->door_map.x + 1;
	dist = (side_pos - game->player.pos.x) / dda->rdir.x;
	if (dist < 0)
		return (-1);
	hit_y = game->player.pos.y + dist * dda->rdir.y;
	if (hit_y < dda->door_map.y + 0.5 - DOOR_THICK / 2)
		return (-1);
	if (hit_y > dda->door_map.y + 0.5 + DOOR_THICK / 2)
		return (-1);
	return (apply_fisheye_correction(game, dda, dist));
}

void	check_door_tile(t_game *game, t_dda *dda, char tile)
{
	double	side_dist;

	dda->door_map.x = dda->map.x;
	dda->door_map.y = dda->map.y;
	dda->door_type = tile;
	if (tile == 'V')
	{
		dda->door_dist = calc_door_dist_v(game, dda);
		side_dist = calc_side_dist_v(game, dda);
	}
	else
	{
		dda->door_dist = calc_door_dist_h(game, dda);
		side_dist = calc_side_dist_h(game, dda);
	}
	if (dda->door_dist > 0)
		dda->hit_door = 1;
	if (side_dist > 0 && (dda->door_dist < 0 || side_dist < dda->door_dist))
	{
		dda->hit_door_side = 1;
		dda->door_side_dist = side_dist;
	}
}
