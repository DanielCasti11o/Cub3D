/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/13 19:55:55 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 'w') // W
		game->keys.w = 1;
	if (keycode == 's') // S
		game->keys.s = 1;
	if (keycode == 'a') // A
		game->keys.a = 1;
	if (keycode == 'd') // D
		game->keys.d = 1;
	if (keycode == 65361) // Left
		game->keys.left = 1;
	if (keycode == 65363) // Right
		game->keys.right = 1;
	if (keycode == 65362) // Up
		game->keys.up = 1;
	if (keycode == 65364) // Down
		game->keys.down = 1;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 'w') // W
		game->keys.w = 0;
	if (keycode == 's') // S
		game->keys.s = 0;
	if (keycode == 'a') // A
		game->keys.a = 0;
	if (keycode == 'd') // D
		game->keys.d = 0;
	if (keycode == 65361) // Left
		game->keys.left = 0;
	if (keycode == 65363) // Right
		game->keys.right = 0;
	if (keycode == 65362) // Up
		game->keys.up = 0;
	if (keycode == 65364) // Down
		game->keys.down = 0;
	return (0);
}

void	rotate_left(t_game *game, double speed)
{
	float	oldir_x;
	float	oldpl_x;

	oldir_x = game->pos.rdir.x;
	oldpl_x = game->pos.plane.x;
	game->pos.rdir.x
		= game->pos.rdir.x * cosf(-speed) - game->pos.rdir.y * sinf(-speed);
	game->pos.rdir.y
		= oldir_x * sinf(-speed) + game->pos.rdir.y * cosf(-speed);
	game->pos.plane.x = game->pos.plane.x * cosf(-speed)
		- game->pos.plane.y * sinf(-speed);
	game->pos.plane.y = oldpl_x * sin(-speed)
		+ game->pos.plane.y * cos(-speed);
}

void	rotate_right(t_game *game, double speed)
{
	float	oldir_x;
	float	oldpl_x;

	oldir_x = game->pos.rdir.x;
	oldpl_x = game->pos.plane.x;
	game->pos.rdir.x
		= game->pos.rdir.x * cosf(speed) - game->pos.rdir.y * sinf(speed);
	game->pos.rdir.y
		= oldir_x * sinf(speed) + game->pos.rdir.y * cosf(speed);
	game->pos.plane.x = game->pos.plane.x * cosf(speed)
		- game->pos.plane.y * sinf(speed);
	game->pos.plane.y = oldpl_x * sin(speed)
		+ game->pos.plane.y * cos(speed);
}

int	ft_events(t_game *game)
{
	double	speed;

	speed = 0.2;
	if (game->keys.left == 1)
		game->pos.angle -= degrees(2);
	if (game->keys.right == 1)
		game->pos.angle += degrees(2);
	if (game->keys.d == 1)
	{
		game->pos.dir.start.x += cos(game->pos.angle + degrees(90)) * speed;
		game->pos.dir.start.y += sin(game->pos.angle + degrees(90)) * speed;
	}
	if (game->keys.a == 1)
	{
		game->pos.dir.start.x += cos(game->pos.angle - degrees(90)) * speed;
		game->pos.dir.start.y += sin(game->pos.angle - degrees(90)) * speed;
	}
	if (game->keys.w == 1)
	{
		game->pos.dir.start.x += cos(game->pos.angle) * speed;
		game->pos.dir.start.y += sin(game->pos.angle) * speed;
	}
	if (game->keys.s == 1)
	{
		game->pos.dir.start.x -= cos(game->pos.angle) * speed;
		game->pos.dir.start.y -= sin(game->pos.angle) * speed;
	}
	if (game->keys.up == 1)
		game->pos.pitch += 10;
	if (game->keys.down == 1)
		game->pos.pitch -= 10;
	clear_image(&game->img_w);
	raycasting(game, game->pos.dir);
	return (0);
}
