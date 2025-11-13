/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:06 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/12 21:16:39 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(t_game *game, t_dda *dda)
{
	if (dda->map.x < 0 || dda->map.x >= game->pos.map.width
		|| dda->map.y < 0 || dda->map.y >= game->pos.map.height)
		return (1);
	if (game->pos.map.grid[dda->map.y][dda->map.x] == '1')
		return (1);
	return (0);
}

void	steps(t_dda *dda, t_vec dir)
{
	if (dir.end.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (dir.start.x - dda->map.x) * dda->deltax;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->map.x + 1.0 - dir.start.x) * dda->deltax;
	}
	if (dir.end.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (dir.start.y - dda->map.y) * dda->deltay;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->map.y + 1.0 - dir.start.y) * dda->deltay;
	}
}

void	fpredrawing(t_vec dir, t_dda *dda, t_game *game)
{
	double	proj_cos;

	if (dda->side == 0)
	{
		dda->ppdist_wall = (dda->map.x - dir.start.x + (1 - dda->step.x) / 2.0)
			/ dir.end.x;
	}
	else
	{
		dda->ppdist_wall = (dda->map.y - dir.start.y + (1 - dda->step.y) / 2.0)
			/ dir.end.y;
	}
	proj_cos = game->pos.rdir.x * dir.end.x + game->pos.rdir.y * dir.end.y;
	if (proj_cos != 0)
		dda->ppdist_wall /= proj_cos;
	if (dda->ppdist_wall < 0.0001)
		dda->ppdist_wall = 0.0001;
	dda->line_height = (int)(HEIGHT / dda->ppdist_wall);
}

void	render_frame(t_game *game, t_dda *dda)
{
	dda->draw_start = HEIGHT / 2 - dda->line_height / 2;
	if (dda->draw_start < 0)
		dda->draw_start = 0;
	dda->draw_end = HEIGHT / 2 + dda->line_height / 2;
	if (dda->draw_end >= HEIGHT)
		dda->draw_end = HEIGHT - 1;
	render_column(game, dda);
	printf("hi start %d \n", dda->draw_start);
}

void	render_column(t_game *game, t_dda *dda)
{
	dda->pdraw.y = 0;
	printf("DEBUG: draw_start = %d\n", dda->draw_start);
	while ((int)dda->pdraw.y < dda->draw_start)
	{
		pixel_image(&game->img_w, dda->pdraw.x, dda->pdraw.y, 0xFFFFFF);
		dda->pdraw.y++;
	}
	printf("sss\n");
	while ((int)dda->pdraw.y <= dda->draw_end)
	{
		pixel_image(&game->img_w, dda->pdraw.x, dda->pdraw.y, 0x0000FF);
		dda->pdraw.y++;
	}
	while ((int)dda->pdraw.y < HEIGHT)
	{
		pixel_image(&game->img_w, dda->pdraw.x, dda->pdraw.y, 0x444444);
		dda->pdraw.y++;
	}
}

void	raycasting(t_game *game, t_vec dir)
{
	t_dda	dda;

	dda.pdraw.x = 0;
	dda.fov = tanf(degrees(33));
	game->pos.rdir.x = cosf(game->pos.angle);
	game->pos.rdir.y = sinf(game->pos.angle);
	game->pos.plane.x = game->pos.rdir.y * dda.fov;
	game->pos.plane.y = -game->pos.rdir.x * dda.fov;
	while (dda.pdraw.x < WIDTH)
	{
		dda.camera_x = 2 * dda.pdraw.x / (double)WIDTH - 1;
		dda.hit = 0;
		dda.map.x = (int)dir.start.x;
		dda.map.y = (int)dir.start.y;
		printf ("x= %zu, y= %zu\n", dda.map.x, dda.map.y);
		dir.end.x = game->pos.rdir.x + game->pos.plane.x * dda.camera_x;
		dir.end.y = game->pos.rdir.y + game->pos.plane.y * dda.camera_x;
		if (fabs(dir.end.x) < 1e-6)
			dda.deltax = 1e30;
		else
			dda.deltax = 1.0 / fabs(dir.end.x);
		if (fabs(dir.end.y) < 1e-6)
			dda.deltay = 1e30;
		else
			dda.deltay = 1.0 / fabs(dir.end.y);
		steps(&dda, dir);
		dda_loop(game, &dda);
		fpredrawing(dir, &dda, game);
		render_frame(game, &dda);
		dda.pdraw.x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
}

void	dda_loop(t_game *game, t_dda *dda)
{
	while (!dda->hit)
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->deltax;
			dda->map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->deltay;
			dda->map.y += dda->step.y;
			dda->side = 1;
		}
		dda->hit = check_hit(game, dda);
	}
}
