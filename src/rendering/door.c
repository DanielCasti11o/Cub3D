/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 04:23:21 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/01 20:35:23 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_draw_limits(int *start, int *end, int line_h, int center)
{
	*start = center - line_h / 2;
	if (*start < 0)
		*start = 0;
	*end = center + line_h / 2;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}

void	calc_door_draw(t_game *game, t_dda *dda)
{
	int	center;

	center = HEIGHT / 2 + game->player.pitch;
	if (dda->hit_door)
	{
		if (dda->door_dist < 0.0001)
			dda->door_dist = 0.0001;
		dda->door_line_height = (int)(HEIGHT / dda->door_dist);
		calc_draw_limits(&dda->door_draw_start, &dda->door_draw_end,
			dda->door_line_height, center);
	}
	if (dda->hit_door_side)
	{
		if (dda->door_side_dist < 0.0001)
			dda->door_side_dist = 0.0001;
		dda->door_side_line_height = (int)(HEIGHT / dda->door_side_dist);
		calc_draw_limits(&dda->door_side_draw_start, &dda->door_side_draw_end,
			dda->door_side_line_height, center);
	}
}

static void	render_door_front(t_game *game, t_dda *dda, t_buf *tex)
{
	t_column	col;
	float		impact;

	if (dda->door_type == 'V')
		impact = game->player.pos.y + dda->door_dist * dda->rdir.y;
	else
		impact = game->player.pos.x + dda->door_dist * dda->rdir.x;
	col.wall_x = impact - floorf(impact);
	col.tex_x = (int)(col.wall_x * (float)tex->width);
	if ((dda->door_type == 'V' && dda->rdir.x < 0)
		|| (dda->door_type == 'H' && dda->rdir.y < 0))
		col.tex_x = (int)((1.0 - col.wall_x) * (float)tex->width);
	col.step = (float)tex->height / (float)dda->door_line_height;
	col.tex_pos = (dda->door_draw_start - (HEIGHT / 2 + game->player.pitch)
			+ dda->door_line_height / 2) * col.step;
	col.y = dda->door_draw_start;
	while (col.y++ <= dda->door_draw_end)
	{
		pixel_image(&game->img, dda->pdraw.x, col.y - 1,
			get_pixel(tex, col.tex_x, (int)col.tex_pos));
		col.tex_pos += col.step;
	}
}

static void	render_door_side(t_game *game, t_dda *dda, t_buf *tex)
{
	t_column	col;

	col.tex_x = tex->width / 2;
	col.step = (float)tex->height / (float)dda->door_side_line_height;
	col.tex_pos = (dda->door_side_draw_start - (HEIGHT / 2 + game->player.pitch)
			+ dda->door_side_line_height / 2) * col.step;
	col.y = dda->door_side_draw_start;
	while (col.y++ <= dda->door_side_draw_end)
	{
		pixel_image(&game->img, dda->pdraw.x, col.y - 1,
			get_pixel(tex, col.tex_x, (int)col.tex_pos));
		col.tex_pos += col.step;
	}
}

void	render_door(t_game *game, t_dda *dda)
{
	t_buf	*tex;

	if (!game->map.tex.door.ptr)
		return ;
	tex = &game->map.tex.door;
	if (dda->hit_door)
		render_door_front(game, dda, tex);
	if (dda->hit_door_side)
		render_door_side(game, dda, tex);
}
