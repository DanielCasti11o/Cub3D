/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:35:50 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/07 22:41:02 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || (BONUS && c == 'D')
		|| is_player_char(c));
}

int	is_void_char(char c)
{
	return (c == ' ' || c == '\0' || c == '\n');
}

int	check_mapspacechar(t_game *game, size_t row, size_t col)
{
	if (row > 0 && (game->map.grid[row - 1][col] == '0'
		|| game->map.grid[row - 1][col] == 'D'
		|| is_player_char(game->map.grid[row - 1][col])))
		return (0);
	return (1);
}

void	assign_doorvalue(t_game *game, size_t row, size_t col)
{
	if ((col > 0 && game->map.grid[row][col - 1] == '1')
		&& (col < game->map.width - 1
			&& game->map.grid[row][col + 1] == '1'))
		game->map.grid[row][col] = 'H';
	else if (row > 0 && game->map.grid[row - 1][col] == '1')
		game->map.grid[row][col] = 'V';
	else if ((col > 0 && game->map.grid[row][col - 1] == '1')
		|| (col < game->map.width - 1
			&& game->map.grid[row][col + 1] == '1'))
		game->map.grid[row][col] = 'H';
	else
		game->map.grid[row][col] = 'V';
}
