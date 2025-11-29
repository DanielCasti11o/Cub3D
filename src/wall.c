/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:09:10 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/29 17:12:17 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_buf	*get_texture_addr(t_game *game, t_dda *dda)
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

static int	get_tex_x(t_dda *dda, t_buf *tex, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (float)tex->width);
	if (dda->side == SIDE_VERTICAL && dda->rdir.x < 0)
		tex_x = (int)((1.0 - wall_x) * (float)tex->width);
	if (dda->side == SIDE_HORIZONTAL && dda->rdir.y < 0)
		tex_x = (int)((1.0 - wall_x) * (float)tex->width);
	return (tex_x);
}

void	render_image_column(t_game *game, t_dda *dda)
{
	t_buf	*tex;
	float	wall_x;
	int		tex_x;
	float	step;
	float	tex_pos;

	tex = get_texture_addr(game, dda);
	wall_x = get_wall_x(game, dda);
	tex_x = get_tex_x(dda, tex, wall_x);
	step = 1.0 * (float)tex->height / (float)dda->line_height;
	tex_pos = (dda->draw_start - (HEIGHT / 2 + game->player.pitch)
			+ dda->line_height / 2) * step;
	while (dda->pdraw.y <= dda->draw_end)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y,
			get_pixel(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		dda->pdraw.y++;
	}
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
	dda->pdraw.y = 0;
	while (dda->pdraw.y < dda->draw_start)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.c);
		dda->pdraw.y++;
	}
	render_image_column(game, dda);
	while (dda->pdraw.y < HEIGHT)
	{
		pixel_image(&game->img, dda->pdraw.x, dda->pdraw.y, game->map.tex.f);
		dda->pdraw.y++;
	}
}
