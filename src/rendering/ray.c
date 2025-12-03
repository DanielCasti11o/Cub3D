/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:06 by dacastil          #+#    #+#             */
/*   Updated: 2025/12/03 18:17:31 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_step(t_dda *dda)
{
	if (dda->side_dist.x < dda->side_dist.y)
	{
		dda->side_dist.x += dda->delta.x;
		dda->map.x += dda->step.x;
		dda->side = SIDE_VERTICAL;
	}
	else
	{
		dda->side_dist.y += dda->delta.y;
		dda->map.y += dda->step.y;
		dda->side = SIDE_HORIZONTAL;
	}
}

static void	dda_loop(t_game *game, t_dda *dda)
{
	char	tile;
	int		in_bounds;

	dda->hit = 0;
	dda->hit_door = 0;
	dda->hit_door_side = 0;
	while (!dda->hit)
	{
		dda_step(dda);
		in_bounds = (dda->map.x >= 0 && dda->map.x < (int)game->map.width
				&& dda->map.y >= 0 && dda->map.y < (int)game->map.height);
		if (in_bounds)
		{
			tile = game->map.grid[dda->map.y][dda->map.x];
			if (!dda->hit_door && !dda->hit_door_side && is_door_tile(tile))
				check_door_tile(game, dda, tile);
		}
		dda->hit = check_hit(game, dda);
	}
}

static void	steps_init(t_game *game, t_dda *dda)
{
	if (dda->rdir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (game->player.pos.x - dda->map.x) * dda->delta.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->map.x + 1.0 - game->player.pos.x)
			* dda->delta.x;
	}
	if (dda->rdir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (game->player.pos.y - dda->map.y) * dda->delta.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->map.y + 1.0 - game->player.pos.y)
			* dda->delta.y;
	}
}

void	render_frame(t_game *game, t_dda *dda)
{
	dda->pdraw.y = 0;
	while (dda->pdraw.y < dda->draw_start)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.c);
		dda->pdraw.y++;
	}
	render_wall_column(game, dda);
	while (dda->pdraw.y < HEIGHT)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.f);
		dda->pdraw.y++;
	}
	render_door(game, dda);
}

void	raycasting(t_game *game)
{
	t_dda	dda;

	game->player.dir.x = cosf(game->player.angle);
	game->player.dir.y = sinf(game->player.angle);
	game->player.plane.x = -game->player.dir.y * game->fov_tan;
	game->player.plane.y = game->player.dir.x * game->fov_tan;
	dda.pdraw.x = 0;
	while (dda.pdraw.x < WIDTH)
	{
		dda.camera_x = 2 * dda.pdraw.x / (double)WIDTH - 1;
		dda.door_type = 0;
		dda.map.x = (int)game->player.pos.x;
		dda.map.y = (int)game->player.pos.y;
		dda.rdir.x = game->player.dir.x + game->player.plane.x * dda.camera_x;
		dda.rdir.y = game->player.dir.y + game->player.plane.y * dda.camera_x;
		dda.delta.x = get_delta_dist(dda.rdir.x);
		dda.delta.y = get_delta_dist(dda.rdir.y);
		steps_init(game, &dda);
		dda_loop(game, &dda);
		calc_wall_draw(game, &dda);
		calc_door_draw(game, &dda);
		render_frame(game, &dda);
		dda.pdraw.x++;
	}
}
