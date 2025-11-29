/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/29 16:51:04 by migugar2         ###   ########.fr       */
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
	if (keycode == 'w')
		game->keys.w = 1;
	if (keycode == 's')
		game->keys.s = 1;
	if (keycode == 'a')
		game->keys.a = 1;
	if (keycode == 'd')
		game->keys.d = 1;
	if (keycode == XK_Left)
		game->keys.left = 1;
	if (keycode == XK_Right)
		game->keys.right = 1;
	if (keycode == XK_Up)
		game->keys.up = 1;
	if (keycode == XK_Down)
		game->keys.down = 1;
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == 'w')
		game->keys.w = 0;
	if (keycode == 's')
		game->keys.s = 0;
	if (keycode == 'a')
		game->keys.a = 0;
	if (keycode == 'd')
		game->keys.d = 0;
	if (keycode == XK_Left)
		game->keys.left = 0;
	if (keycode == XK_Right)
		game->keys.right = 0;
	if (keycode == XK_Up)
		game->keys.up = 0;
	if (keycode == XK_Down)
		game->keys.down = 0;
	return (0);
}

int	ft_events(t_game *game)
{
	if (game->keys.left == 1)
		game->player.angle -= degrees(0.5);
	if (game->keys.right == 1)
		game->player.angle += degrees(0.5);
	if (game->keys.d == 1)
		lateral_transition(RIGHT, game);
	if (game->keys.a == 1)
		lateral_transition(LEFT, game);
	if (game->keys.w == 1)
		move_vector_view(FRONT, game);
	if (game->keys.s == 1)
		move_vector_view(BACK, game);
	if (game->keys.up == 1)
		game->player.pitch += 5;
	if (game->keys.down == 1)
		game->player.pitch -= 5;
	clear_image(&game->img);
	raycasting(game);
	mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
