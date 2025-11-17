/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/17 21:14:16 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_game *game)
{
	free_end(game);
	exit(0);
	return (0);
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		return (ft_close(game));
	if (keycode == 'w') // W
		game->keys.w = 1;
	if (keycode == 's') // S
		game->keys.s = 1;
	if (keycode == 'a') // A
		game->keys.a = 1;
	if (keycode == 'd') // D
		game->keys.d = 1;
	if (keycode == XK_Left) // Left
		game->keys.left = 1;
	if (keycode == XK_Right) // Right
		game->keys.right = 1;
	if (keycode == XK_Up) // Up
		game->keys.up = 1;
	if (keycode == XK_Down) // Down
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
	if (keycode == XK_Left) // Left
		game->keys.left = 0;
	if (keycode == XK_Right) // Right
		game->keys.right = 0;
	if (keycode == XK_Up) // Up
		game->keys.up = 0;
	if (keycode == XK_Down) // Down
		game->keys.down = 0;
	return (0);
}

void	rotate_left(t_game *game, double speed)
{
	float	oldir_x;
	float	oldpl_x;

	oldir_x = game->player.dir.x;
	oldpl_x = game->player.plane.x;
	game->player.dir.x
		= game->player.dir.x * cosf(-speed) - game->player.dir.y * sinf(-speed);
	game->player.dir.y
		= oldir_x * sinf(-speed) + game->player.dir.y * cosf(-speed);
	game->player.plane.x = game->player.plane.x * cosf(-speed)
		- game->player.plane.y * sinf(-speed);
	game->player.plane.y = oldpl_x * sinf(-speed)
		+ game->player.plane.y * cosf(-speed);
}

void	rotate_right(t_game *game, double speed)
{
	float	oldir_x;
	float	oldpl_x;

	oldir_x = game->player.dir.x;
	oldpl_x = game->player.plane.x;
	game->player.dir.x
		= game->player.dir.x * cosf(speed) - game->player.dir.y * sinf(speed);
	game->player.dir.y
		= oldir_x * sinf(speed) + game->player.dir.y * cosf(speed);
	game->player.plane.x = game->player.plane.x * cosf(speed)
		- game->player.plane.y * sinf(speed);
	game->player.plane.y = oldpl_x * sinf(speed)
		+ game->player.plane.y * cosf(speed);
}

int	ft_events(t_game *game)
{
	double	speed;

	speed = 0.2;
	if (game->keys.left == 1)
		game->player.angle -= degrees(2);
	if (game->keys.right == 1)
		game->player.angle += degrees(2);
	if (game->keys.d == 1)
	{
		game->player.pos.x += cosf(game->player.angle + degrees(90)) * speed;
		game->player.pos.y += sinf(game->player.angle + degrees(90)) * speed;
	}
	if (game->keys.a == 1)
	{
		game->player.pos.x += cosf(game->player.angle - degrees(90)) * speed;
		game->player.pos.y += sinf(game->player.angle - degrees(90)) * speed;
	}
	if (game->keys.w == 1)
	{
		game->player.pos.x += cosf(game->player.angle) * speed;
		game->player.pos.y += sinf(game->player.angle) * speed;
	}
	if (game->keys.s == 1)
	{
		game->player.pos.x -= cosf(game->player.angle) * speed;
		game->player.pos.y -= sinf(game->player.angle) * speed;
	}
	if (game->keys.up == 1)
		game->player.pitch += 10;
	if (game->keys.down == 1)
		game->player.pitch -= 10;
	clear_image(&game->img);
	raycasting(game);
	return (0);
}
