/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:23:04 by dacastil          #+#    #+#             */
/*   Updated: 2025/12/03 18:18:22 by migugar2         ###   ########.fr       */
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
