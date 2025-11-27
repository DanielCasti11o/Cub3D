/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/22 18:31:57 by daniel-cast      ###   ########.fr       */
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

void	move_vector_view(int type, t_game *game)
{
	t_vec2f	new_pos;
	double	speed;

	speed = 0.03;
	if (type == FRONT)
	{
		new_pos.x = game->player.pos.x + cosf(game->player.angle) * speed;
		new_pos.y = game->player.pos.y + sinf(game->player.angle) * speed;
	}
	if (type == BACK)
	{
		new_pos.x = game->player.pos.x - cosf(game->player.angle) * speed;
		new_pos.y = game->player.pos.y - sinf(game->player.angle) * speed;
	}
	if (game->map.grid[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

void	lateral_transition(int type, t_game *game)
{
	t_vec2f	new_pos;
	double	speed;

	speed = 0.03;
	if (type == RIGHT)
	{
		new_pos.x = game->player.pos.x + cosf(game->player.angle + degrees(90)) * speed;
		new_pos.y = game->player.pos.y + sinf(game->player.angle + degrees(90)) * speed;
	}
	if (type == LEFT)
	{
		new_pos.x = game->player.pos.x + cosf(game->player.angle - degrees(90)) * speed;
		new_pos.y = game->player.pos.y + sinf(game->player.angle - degrees(90)) * speed;
	}
	if (game->map.grid[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
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
