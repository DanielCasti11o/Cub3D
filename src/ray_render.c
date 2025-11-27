/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:09:10 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/27 21:39:57 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (dda->pdraw.y <= dda->draw_end)
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
}
