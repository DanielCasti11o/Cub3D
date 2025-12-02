/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_minmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:47:53 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/12/02 16:38:13 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_playermap	p_init(t_game *game)
{
	t_playermap	pmap;

	pmap.pos_float.x = game->player.pos.x - floor(game->player.pos.x);
	pmap.pos_float.y = game->player.pos.y - floor(game->player.pos.y);
	pmap.center_px.x = game->mp.edge_x + (10 * game->mp.scale);
	pmap.center_px.y = game->mp.edge_y + (10 * game->mp.scale);
	pmap.player_px.x = pmap.center_px.x
		+ (int)(pmap.pos_float.x * game->mp.scale);
	pmap.player_px.y = pmap.center_px.y
		+ (int)(pmap.pos_float.y * game->mp.scale);
	pmap.scale_player = 10;
	pmap.center = pmap.scale_player / 2;
	return (pmap);
}

void	big_render_player(t_game *game)
{
	t_playermap	pmap;
	t_vec2i		count;

	pmap = p_init(game);
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

void	draw_map(t_game *game, t_vec2i px, t_vec2i map)
{
	if (map.x >= 0 && map.x < (int)game->map.width
		&& map.y >= 0 && map.y < (int)game->map.height)
	{
		if (game->map.grid[map.y][map.x] == '1')
			draw_square(game, px.x, px.y, game->mp.color_wall);
		else if (game->map.grid[map.y][map.x] == 'H'
				|| game->map.grid[map.y][map.x] == 'V')
			draw_square(game, px.x, px.y, 0xff00ff);
		else if (game->map.grid[map.y][map.x] == '0'
		|| ft_strchr("NSEW", game->map.grid[map.y][map.x]))
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
