/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:06 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/22 19:13:21 by daniel-cast      ###   ########.fr       */
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

void	steps_init(t_game *game, t_dda *dda)
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

void	fpredrawing(t_game *game, t_dda *dda)
{
	double	proj_cos;

	if (dda->side == SIDE_VERTICAL)
	{
		dda->ppdist_wall = (dda->map.x - game->player.pos.x + (1 - dda->step.x)
				/ 2.0) / dda->rdir.x;
	}
	else
	{
		dda->ppdist_wall = (dda->map.y - game->player.pos.y + (1 - dda->step.y)
				/ 2.0) / dda->rdir.y;
	}
	proj_cos = game->player.dir.x * dda->rdir.x + game->player.dir.y
		* dda->rdir.y;
	if (proj_cos != 0)
		dda->ppdist_wall /= proj_cos;
	if (dda->ppdist_wall < 0.0001)
		dda->ppdist_wall = 0.0001;
	dda->line_height = (int)(HEIGHT / dda->ppdist_wall);
}

void	render_frame(t_game *game, t_dda *dda)
{
	int	center;

	center = HEIGHT / 2 + game->player.pitch;
	dda->draw_start = center - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = center + dda->line_height / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
	render_column(game, dda);
	// printf("hi start %d \n", dda->draw_start);
}

void	render_image_column(t_game *game, t_dda *dda)
{
	float	dec;
	float	step;
	int		tex_x;
	float	impact;
	float	tex_pos;
	t_buf	*texture;

	if (dda->side == SIDE_VERTICAL)
		impact = (game->player.pos.y + dda->ppdist_wall * dda->rdir.y);
	else
		impact = (game->player.pos.x + dda->ppdist_wall * dda->rdir.x);
	dec = impact - floorf(impact);
	if (dda->side == SIDE_VERTICAL && dda->rdir.x > 0)
	{
		texture = &game->map.tex.ea;
		tex_x = (int)(dec * (float)game->map.tex.ea.width);
		step = 1.0 * (float)(game->map.tex.ea.height) / (float)(dda->line_height);
	}
	else if (dda->side == SIDE_VERTICAL && dda->rdir.x < 0)
	{
		texture = &game->map.tex.we;
		tex_x = (int)((1.0 - dec) * (float)game->map.tex.we.width);
		step = 1.0 * (float)(game->map.tex.we.height) / (float)(dda->line_height);
	}
	else if (dda->side == SIDE_HORIZONTAL && dda->rdir.y > 0)
	{
		texture = &game->map.tex.so;
		tex_x = (int)(dec * (float)game->map.tex.so.width);
		step = 1.0 * (float)(game->map.tex.so.height) / (float)(dda->line_height);
	}
	else
	{
		texture = &game->map.tex.no;
		tex_x = (int)((1.0 - dec) * (float)game->map.tex.no.width);
		step = 1.0 * (float)(game->map.tex.no.height) / (float)(dda->line_height);
	}
	tex_pos = (dda->draw_start - (HEIGHT / 2 + game->player.pitch)
			+ dda->line_height / 2) * step;
	while ((int)dda->pdraw.y <= dda->draw_end)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y,
			get_pixel(texture, tex_x, (int)tex_pos));
		tex_pos += step;
		dda->pdraw.y++;
	}
}

void	render_column(t_game *game, t_dda *dda)
{
	dda->pdraw.y = 0;
	// printf("DEBUG: draw_start = %d\n", dda->draw_start);
	while ((int)dda->pdraw.y < dda->draw_start)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.c);
		dda->pdraw.y++;
	}
	render_image_column(game, dda);
	while ((int)dda->pdraw.y < HEIGHT)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.f);
		dda->pdraw.y++;
	}
}

// TODO: check uninitialized values in dda struct

void	raycasting(t_game *game)
{
	t_dda	dda;

	dda.pdraw.x = 0;
	game->player.dir.x = cosf(game->player.angle);
	game->player.dir.y = sinf(game->player.angle);
	game->player.plane.x = -game->player.dir.y * game->fov_tan;
	game->player.plane.y = game->player.dir.x * game->fov_tan;
	while (dda.pdraw.x < WIDTH)
	{
		dda.camera_x = 2 * dda.pdraw.x / (double)WIDTH - 1;
		dda.hit = 0;
		dda.map.x = (size_t)game->player.pos.x;
		dda.map.y = (size_t)game->player.pos.y;
		// printf ("x= %zu, y= %zu\n", dda.map.x, dda.map.y);
		dda.rdir.x = game->player.dir.x + game->player.plane.x * dda.camera_x;
		dda.rdir.y = game->player.dir.y + game->player.plane.y * dda.camera_x;
		if (fabsf(dda.rdir.x) < 1e-6)
			dda.delta.x = 1e30;
		else
			dda.delta.x = 1.0 / fabs(dda.rdir.x);
		if (fabsf(dda.rdir.y) < 1e-6)
			dda.delta.y = 1e30;
		else
			dda.delta.y = 1.0 / fabs(dda.rdir.y);
		steps_init(game, &dda);
		dda_loop(game, &dda);
		fpredrawing(game, &dda);
		render_frame(game, &dda);
		dda.pdraw.x++;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

void	dda_loop(t_game *game, t_dda *dda)
{
	while (!dda->hit)
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
		dda->hit = check_hit(game, dda);
	}
}
