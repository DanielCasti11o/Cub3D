/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/21 17:10:04 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 13) // W
		game->keys.w = 1;
	if (keycode == 1) // S
		game->keys.s = 1;
	if (keycode == 0) // A
		game->keys.a = 1;
	if (keycode == 2) // D
		game->keys.d = 1;
	if (keycode == 123) // Left
		game->keys.left = 1;
	if (keycode == 124) // Right
		game->keys.right = 1;
	if (keycode == 126) // Up
		game->keys.up = 1;
	if (keycode == 125) // Down
		game->keys.down = 1;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
		if (keycode == 13) // W
		game->keys.w = 0;
	if (keycode == 1) // S
		game->keys.s = 0;
	if (keycode == 0) // A
		game->keys.a = 0;
	if (keycode == 2) // D
		game->keys.d = 0;
	if (keycode == 123) // Left
		game->keys.left = 0;
	if (keycode == 124) // Right
		game->keys.right = 0;
	if (keycode == 126) // Up
		game->keys.up = 0;
	if (keycode == 125) // Down
		game->keys.down = 0;
	return (0);
}

int	ft_events(t_game *game)
{
	if (game->keys.left)
		game->vision.angle += 1.0;
	if (game->keys.right)
		game->vision.angle -= 1.0;
	mlx_clear_window(game->mlx, game->win);
	return (0);
}
