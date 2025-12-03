/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_minmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:47:53 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/12/03 17:02:45 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	big_render_player(t_game *game)
{
	t_playermap	pmap;
	t_vec2i		count;

	pmap.pos_float.x = game->player.pos.x - floorf(game->player.pos.x);
	pmap.pos_float.y = game->player.pos.y - floorf(game->player.pos.y);
	pmap.center_px.x = game->mp.edge_x + (10 * game->mp.scale);
	pmap.center_px.y = game->mp.edge_y + (10 * game->mp.scale);
	pmap.player_px.x = pmap.center_px.x
		+ (int)(pmap.pos_float.x * game->mp.scale);
	pmap.player_px.y = pmap.center_px.y
		+ (int)(pmap.pos_float.y * game->mp.scale);
	pmap.scale_player = 10;
	pmap.center = pmap.scale_player / 2;
	count.y = 0;
	while (count.y < pmap.scale_player)
	{
		count.x = 0;
		while (count.x < pmap.scale_player)
		{
			pixel_image(&game->img, pmap.player_px.x + count.x - pmap.center,
				pmap.player_px.y + count.y - pmap.center, 0xff0000);
			count.x++;
		}
		count.y++;
	}
}

static void	draw_door_tile(t_game *game, t_vec2i px, t_vec2i count, int type)
{
	if (type == 'V')
	{
		if (count.x >= ((game->mp.scale / 2) - 2)
			&& count.x <= (game->mp.scale / 2) + 2)
			pixel_image(&game->img, px.x + count.x, px.y + count.y, 0x00A52A2A);
		else
			pixel_image(&game->img, px.x + count.x, px.y + count.y,
				game->mp.color_floor);
	}
	else if (type == 'H')
	{
		if (count.y >= ((game->mp.scale / 2) - 2)
			&& count.y <= (game->mp.scale / 2) + 2)
			pixel_image(&game->img, px.x + count.x, px.y + count.y, 0x00A52A2A);
		else
			pixel_image(&game->img, px.x + count.x, px.y + count.y,
				game->mp.color_floor);
	}
}

void	draw_door(t_game *game, t_vec2i px, int type)
{
	t_vec2i	count;

	count.y = 0;
	while (count.y < game->mp.scale)
	{
		count.x = 0;
		while (count.x < game->mp.scale)
		{
			draw_door_tile(game, px, count, type);
			count.x++;
		}
		count.y++;
	}
}

void	draw_map(t_game *game, t_vec2i px, t_vec2i map)
{
	if (map.x >= 0 && map.x < (int)game->map.width
		&& map.y >= 0 && map.y < (int)game->map.height)
	{
		if (game->map.grid[map.y][map.x] == '1')
			draw_square(game, px.x, px.y, game->mp.color_wall);
		else if (game->map.grid[map.y][map.x] == 'H'
			|| game->map.grid[map.y][map.x] == 'V')
			draw_door(game, px, game->map.grid[map.y][map.x]);
		else if (game->map.grid[map.y][map.x] == '0'
		|| is_player_char(game->map.grid[map.y][map.x]))
			draw_square(game, px.x, px.y, game->mp.color_floor);
	}
	else
		draw_square(game, px.x, px.y, game->mp.color_wall);
}

void	big_render_minmap(t_game *game)
{
	t_vec2i	vec;
	t_vec2i	px;
	t_vec2i	map;
	int		tiles;

	tiles = M_SIZE / game->mp.scale;
	vec.y = 0;
	while (vec.y < tiles)
	{
		map.y = (int)game->player.pos.y - (tiles / 2) + vec.y;
		vec.x = 0;
		while (vec.x < tiles)
		{
			map.x = (int)game->player.pos.x - (tiles / 2) + vec.x;
			px.x = game->mp.edge_x + (vec.x * game->mp.scale);
			px.y = game->mp.edge_y + (vec.y * game->mp.scale);
			draw_map(game, px, map);
			vec.x++;
		}
		vec.y++;
	}
}
