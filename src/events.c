/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/28 20:25:50 by daniel-cast      ###   ########.fr       */
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

int	ft_events(t_game *game)
{
	if (game->keys.left == 1)
		game->vision.angle -= degrees(2);
	if (game->keys.right == 1)
		game->vision.angle += degrees(2);
	if (game->keys.d == 1)
		game->pos.x += 0.8;
	if (game->keys.a == 1)
		game->pos.x -= 0.8;
	if (game->keys.w == 1)
		game->pos.y -= 0.8;
	if (game->keys.s == 1)
		game->pos.y += 0.8;
	clear_image(&game->img_w);
	loop_ray(game);
	return (0);
}
