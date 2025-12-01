/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:09:10 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/01 20:23:15 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall_draw(t_game *game, t_dda *dda)
{
	int		center;
	double	dist;

	if (dda->side == SIDE_VERTICAL)
		dist = (dda->map.x - game->player.pos.x + (1 - dda->step.x) / 2.0)
			/ dda->rdir.x;
	else
		dist = (dda->map.y - game->player.pos.y + (1 - dda->step.y) / 2.0)
			/ dda->rdir.y;
	dda->ppdist_wall = apply_fisheye_correction(game, dda, dist);
	dda->line_height = (int)(HEIGHT / dda->ppdist_wall);
	center = HEIGHT / 2 + game->player.pitch;
	dda->draw_start = center - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = center + dda->line_height / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
}

static t_buf	*get_wall_texture(t_game *game, t_dda *dda)
{
	if (dda->side == SIDE_VERTICAL)
	{
		if (dda->rdir.x > 0)
			return (&game->map.tex.ea);
		return (&game->map.tex.we);
	}
	if (dda->rdir.y > 0)
		return (&game->map.tex.so);
	return (&game->map.tex.no);
}

static float	get_wall_x(t_game *game, t_dda *dda)
{
	float	impact;

	if (dda->side == SIDE_VERTICAL)
		impact = game->player.pos.y + dda->ppdist_wall * dda->rdir.y;
	else
		impact = game->player.pos.x + dda->ppdist_wall * dda->rdir.x;
	return (impact - floorf(impact));
}

void	render_wall_column(t_game *game, t_dda *dda)
{
	t_buf		*tex;
	t_column	col;

	tex = get_wall_texture(game, dda);
	col.wall_x = get_wall_x(game, dda);
	col.tex_x = (int)(col.wall_x * (float)tex->width);
	if (dda->side == SIDE_VERTICAL && dda->rdir.x < 0)
		col.tex_x = tex->width - col.tex_x - 1;
	if (dda->side == SIDE_HORIZONTAL && dda->rdir.y < 0)
		col.tex_x = tex->width - col.tex_x - 1;
	col.step = (float)tex->height / (float)dda->line_height;
	col.tex_pos = (dda->draw_start - (HEIGHT / 2 + game->player.pitch)
			+ dda->line_height / 2) * col.step;
	while (dda->pdraw.y <= dda->draw_end)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y,
			get_pixel(tex, col.tex_x, (int)col.tex_pos));
		col.tex_pos += col.step;
		dda->pdraw.y++;
	}
}
