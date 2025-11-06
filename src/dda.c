/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 23:04:02 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/05 19:34:41 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray(t_game *game)
{
	game->pos.ray_x = game->pos.x;
	game->pos.ray_y = game->pos.y;
	while (1)
	{
		game->pos.ray_x += game->pos.to_x * 0.1;
		game->pos.ray_y += game->pos.to_y * 0.1;
		pixel_image(&game->img_w, game->pos.ray_x, game->pos.ray_y, 0xFF0000);
		if (game->pos.ray_y >= HEIGHT || game->pos.ray_x >= WIDTH
			|| game->pos.ray_x <= 0 || game->pos.ray_y <= 0)
			break ;
	}
}

void	loop_ray(t_game *game)
{
	double	limit;
	bool	complete;

	limit = game->vision.angle;
	complete = false;
	pixel_image(&game->img_w, game->pos.x, game->pos.y, 0xFFFFFF);
	game->pos.to_x = cos(game->vision.angle);
	game->pos.to_y = sin(game->vision.angle);
	ray(game);
	while (game->vision.angle > (limit - degrees(30)))
	{
		while (complete == false)
		{
			game->vision.angle += degrees(0.1); // Menos de un grado
			game->pos.to_x = cos(game->vision.angle);
			game->pos.to_y = sin(game->vision.angle);
			// game->pos.delta_x = fabs(1 / game->pos.to_x);
			// game->pos.delta_y = fabs(1 / game->pos.to_y);
			ray(game);
			if (game->vision.angle > (limit + degrees(30)))
			{
				complete = true;
				game->vision.angle = limit;
			}
		}
		game->vision.angle -= degrees(0.1);
		game->pos.to_x = cos(game->vision.angle);
		game->pos.to_y = sin(game->vision.angle);
		ray(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
	game->vision.angle = limit;
}
