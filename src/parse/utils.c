/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:35:50 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/13 20:14:20 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	preinit_parse(t_game *game, t_parse *parse)
{
	game->map.height = 0;
	parse->first_v_char = -1;
	parse->last_v_char = 0;
	parse->head_map = NULL;
	parse->tail_map = NULL;
	parse->state = SP_HEADER;
	game->infile.c = color_rgba(0, 0, 0, 0);
	game->infile.f = color_rgba(0, 0, 0, 0);
	game->infile.no = NULL;
	game->infile.so = NULL;
	game->infile.we = NULL;
	game->infile.ea = NULL;
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || is_player_char(c));
}

int	is_void_char(char c)
{
	return (c == ' ' || c == '\0' || c == '\n');
}

int	check_mapspacechar(t_game *game, size_t row, size_t col)
{
	if (row > 0 && (game->map.grid[row - 1][col] == '0'
		|| is_player_char(game->map.grid[row - 1][col])))
		return (0);
	return (1);
}
