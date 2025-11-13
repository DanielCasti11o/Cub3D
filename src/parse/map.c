/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:45:49 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/07 22:05:38 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_alloc(t_game *game, t_parse *parse)
{
	size_t	i;

	game->pos.map.width = parse->last_v_char - parse->first_v_char;
	game->pos.map.grid = malloc(sizeof(char *) * (game->pos.map.height + 1));
	if (game->pos.map.grid == NULL)
		return (perror_malloc());
	game->pos.map.grid[game->pos.map.height] = NULL;
	i = 0;
	while (i < game->pos.map.height)
	{
		game->pos.map.grid[i] = malloc(sizeof(char) * (game->pos.map.width
					+ 1));
		if (game->pos.map.grid[i] == NULL)
			return (perror_malloc());
		game->pos.map.grid[i][0] = '\0';
		game->pos.map.grid[i][game->pos.map.width] = '\0';
		i++;
	}
	parse->player_start_x = -1;
	parse->player_start_y = -1;
	return (0);
}

static int	map_charcheck(t_game *game, t_parse *parse, size_t row, size_t cur)
{
	size_t		col;
	const char	*line;

	line = parse->head_map->content;
	if (!is_map_char(line[cur]))
		return (perror_unexpectedchar(line[cur]), 1);
	col = cur - parse->first_v_char;
	if (is_player_char(line[cur]))
	{
		if (parse->player_start_x != -1 && parse->player_start_y != -1)
			return (perror_multipleplayerstart(), 1);
		parse->player_start_y = row;
		parse->player_start_x = col;
	}
	if (line[cur] == '0' || is_player_char(line[cur]))
	{
		if (row == 0 || is_void_char(game->pos.map.grid[row - 1][col])
			|| col == 0 || is_void_char(line[cur - 1])
			|| col == game->pos.map.width - 1 || is_void_char(line[cur + 1])
			|| row == game->pos.map.height - 1)
			return (perror_unclosedmap());
	}
	if (line[cur] == ' ' && check_mapspacechar(game, row, col) == 0)
		return (perror_unclosedmap());
	return (0);
}

static int	map_buildrow(t_game *game, t_parse *parse, size_t row)
{
	size_t		col;
	const char	*line;
	ssize_t		cur;

	line = parse->head_map->content;
	cur = parse->first_v_char;
	while (line[cur] != '\0' && line[cur] != '\n' && cur < parse->last_v_char)
	{
		if (map_charcheck(game, parse, row, cur) == 1)
			return (1);
		col = cur - parse->first_v_char;
		game->pos.map.grid[row][col] = line[cur];
		cur++;
	}
	while (cur < parse->last_v_char)
	{
		col = cur - parse->first_v_char;
		game->pos.map.grid[row][col] = ' ';
		if (check_mapspacechar(game, row, col) == 0)
			return (perror_unclosedmap());
		cur++;
	}
	return (0);
}

static void	map_setplayer(t_game *game, t_parse *parse)
{
	char	dir;

	game->pos.dir.start.x = parse->player_start_x + 0.5f;
	game->pos.dir.start.y = parse->player_start_y + 0.5f;
	dir = game->pos.map.grid[parse->player_start_y][parse->player_start_x];
	if (dir == 'N')
	{
		game->pos.dir.end.x = 0.0f;
		game->pos.dir.end.y = -1.0f;
	}
	else if (dir == 'S')
	{
		game->pos.dir.end.x = 0.0f;
		game->pos.dir.end.y = 1.0f;
	}
	else if (dir == 'E')
	{
		game->pos.dir.end.x = 1.0f;
		game->pos.dir.end.y = 0.0f;
	}
	else if (dir == 'W')
	{
		game->pos.dir.end.x = -1.0f;
		game->pos.dir.end.y = 0.0f;
	}
}

int	parse_map(t_game *game, t_parse *parse)
{
	size_t	row;
	t_list	*next;

	if (parse->head_map == NULL)
		return (0);
	if (map_alloc(game, parse) == 1)
		return (1);
	row = 0;
	while (row < game->pos.map.height)
	{
		if (map_buildrow(game, parse, row) == 1)
			return (ft_freestr(&game->pos.map.grid[row]), 1);
		next = parse->head_map->next;
		ft_lstdelone(&parse->head_map, free);
		parse->head_map = next;
		row++;
	}
	parse->tail_map = NULL;
	if (parse->player_start_x == -1 || parse->player_start_y == -1)
		return (perror_noplayerstart(), 1);
	map_setplayer(game, parse);
	parse->seen |= E_MAP;
	return (0);
}
