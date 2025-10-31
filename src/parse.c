/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/31 17:52:50 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: Idea is: store state, read line by line, parse depending on state, when map starts, parse map until end of file

// TODO: For map parsing, I can store lines in a linked list, checking only the max size, and being sure that not empty lines are in the middle

// * If len is lower than 1, it's an empty line, if it's an empty line state must be SP_DONE, but if after that there is a non empty line, it's an error

static int	save_mapline(t_game *game, t_parse *parse, char *line, ssize_t len)
{
	size_t	i;
	t_list	*new_node;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (len == 0 || line[i] == '\0' || line[i] == '\n')
		return (parse->state = SP_DONE, 0);
	else if (parse->state == SP_DONE)
		return (perror_emptylineinmap(), 1);
	new_node = ft_lstnew(line);
	if (new_node == NULL)
		return (perror_malloc());
	if (parse->head_map == NULL)
		parse->head_map = new_node;
	else
		parse->tail_map->next = new_node;
	parse->tail_map = new_node;
	while (len > 0 && (ft_isspace(line[len - 1]) || line[len - 1] == '\n'))
		len--;
	if (parse->first_v_char == -1 || i < (size_t)parse->first_v_char)
		parse->first_v_char = i;
	if (len > parse->last_v_char)
		parse->last_v_char = len;
	return (game->parse.map.height++, 0);
}

static int	parse_textpath(t_game *game, t_elemfile elem, char *line)
{
	size_t	len;
	char	*path;
	size_t	start;

	start = 0;
	while (ft_isspace(line[start]))
		start++;
	len = 0;
	while (line[start + len] != '\0' && line[start + len] != '\n')
		len++;
	while (len > 0 && ft_isspace(line[start + len - 1]))
		len--;
	if (len == 0)
		return (perror_emptyarg(elem));
	// TODO: must check if file is .xpm? Or let mlx handle it later? (for different formats)
	path = ft_substr(line, start, len);
	if (path == NULL)
		return (perror_malloc());
	if (elem == E_NO)
		game->parse.no = path;
	else if (elem == E_SO)
		game->parse.so = path;
	else if (elem == E_WE)
		game->parse.we = path;
	else if (elem == E_EA)
		game->parse.ea = path;
	return (0);
}

static int	parse_color_component(char **str, uint8_t *component)
{
	int	value;

	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (perror_unexpectedchar(**str), 1);
	value = 0;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (perror_overflow(), 1);
		(*str)++;
	}
	*component = (uint8_t)value;
	while (ft_isspace(**str))
		(*str)++;
	return (0);
}

static int	parse_color(t_game *game, t_elemfile type, char *line)
{
	t_color	*color;

	if (type == E_F)
		color = &game->parse.f;
	else
		color = &game->parse.c;
	if (parse_color_component(&line, &color->r) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->g) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->b) == 1)
		return (1);
	if (*line != '\n' && *line != '\0')
		return (perror_unexpectedchar(*line), 1);
	color->a = 255;
	return (0);
}

// TODO: Should we skip empty start in header lines?
static t_elemfile	identify_element(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((*line)[0] == 'N' && (*line)[1] == 'O')
		return (*line += 2, E_NO);
	else if ((*line)[0] == 'S' && (*line)[1] == 'O')
		return (*line += 2, E_SO);
	else if ((*line)[0] == 'W' && (*line)[1] == 'E')
		return (*line += 2, E_WE);
	else if ((*line)[0] == 'E' && (*line)[1] == 'A')
		return (*line += 2, E_EA);
	else if ((*line)[0] == 'F')
		return (*line += 1, E_F);
	else if ((*line)[0] == 'C')
		return (*line += 1, E_C);
	if ((*line)[0] == '1' || (*line)[0] == '0' || (*line)[0] == 'N'
		|| (*line)[0] == 'S' || (*line)[0] == 'E' || (*line)[0] == 'W')
		return (E_MAP);
	else if (**line == '\0' || **line == '\n')
		return (E_EMPTY);
	return (E_INVALID);
}

static int	parse_header(t_game *game, char	*line, t_parse	*parse)
{
	t_elemfile	type;

	type = identify_element(&line);
	if (type == E_INVALID)
		return (perror_unexpectedchar(*line));
	else if (type == E_EMPTY)
		return (0);
	else if (type == E_MAP)
	{
		if (parse->seen != (E_NO | E_SO | E_WE | E_EA | E_F | E_C))
			return (parse->seen |= E_MAP, perror_missingelements(parse->seen));
		parse->state = SP_MAP;
		return (0);
	}
	if (parse->seen & type)
		return (perror_alreadydefined(type));
	parse->seen |= type;
	if (!ft_isspace(*line))
		return (perror_unexpectedchar(*line));
	if (type == E_C || type == E_F)
		return (parse_color(game, type, line));
	return (parse_textpath(game, type, line));
}

int	parse_stream(t_game *game, t_parse *parse, int fd, char *filename)
{
	char		*line;
	ssize_t		bytes_read;

	parse->seen = 0;
	while (1)
	{
		line = NULL;
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (perror_gnl(filename), ft_freestr(&line), 1);
		if (bytes_read == 0)
			break ;
		if (parse->state == SP_HEADER)
		{
			if (parse_header(game, line, parse) == 1)
				return (ft_freestr(&line), 1);
			if (parse->state != SP_MAP)
				ft_freestr(&line);
		}
		if (parse->state == SP_MAP || parse->state == SP_DONE)
			if (save_mapline(game, parse, line, bytes_read) == 1)
				return (ft_freestr(&line), 1);
	}
	return (0);
}

int	parse_map(t_game *game, t_parse *parse)
{
	game->parse.map.width = parse->last_v_char - parse->first_v_char;
	printf("Size of map to parse: width %zu, height %zu\n" , game->parse.map.width, game->parse.map.height);

	// TODO
	(void)game;
	ft_lstclear(&parse->head_map, free);
	return (0);
}

int	parse_game(t_game *game, int argc, char **argv)
{
	t_parse		parse;
	size_t		len;
	int			fd;

	if (argc != 2)
		return (perror_args());
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		return (perror_filename());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror_open(argv[1]));
	game->parse.map.height = 0;
	parse.head_map = NULL;
	parse.tail_map = NULL;
	parse.first_v_char = -1;
	parse.last_v_char = 0;
	parse.state = SP_HEADER;
	if (parse_stream(game, &parse, fd, argv[1]) == 1)
		return (close(fd), ft_lstclear(&parse.head_map, free), 1);
	close(fd);
	if (parse_map(game, &parse) == 1)
		return (ft_lstclear(&parse.head_map, free), 1);
	if (parse.seen != (E_NO | E_SO | E_WE | E_EA | E_F | E_C | E_MAP))
		return (perror_missingelements(parse.seen),
			ft_lstclear(&parse.head_map, free), 1);
	return (0);
}

/*
static int	read_file(int fd, char *filename, t_list **head)
{
	t_list	*tail;
	char	*line;
	ssize_t	bytes_read;
	t_list	*new_node;

	tail = NULL;
	line = NULL;
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (perror_gnl(filename),
				ft_freestr(&line), ft_lstclear(&head, free), NULL);
		if (bytes_read == 0)
			break ;
		new_node = ft_lstnew(*line);
		if (new_node == NULL)
			return (perror_malloc());
		if (*head == NULL)
			*head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
	}
	return (head);
}

// TODO: The problem here is that it's a problem to enter a line with a size bigger or lower, I can fix it with padding the lines with spaces to the max width after reading all map lines
// TODO: I can create an automata for reading all the file, with states during the reading
// TODO
static int	parse_mapline(t_game *game, char *line, char *bef, char	*aft)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
	{
		if (line[len] != ' ' && line[len] != '0' && line[len] != '1'
			&& line[len] != 'N' && line[len] != 'S' && line[len] != 'E'
			&& line[len] != 'W')
			return (perror_unexpectedchar(line[len]), 1);
		if (line[len] == 'N' || line[len] == 'S'
			|| line[len] == 'E' || line[len] == 'W')
		{
			if (game->parse.map.player_start_x != -1
				&& game->parse.map.player_start_y != -1)
				return (perror_multipleplayer(), 1);
			game->parse.map.player_start_y = game->parse.map.height;
			game->parse.map.player_start_x = len;
		}
		if (line[len] == 'N' || line[len] == 'S'
			|| line[len] == 'E' || line[len] == 'W' || line[len] == '0')
		{
			if (bef != NULL)
			{
				i = 0;
				while (bef[i] != '\0' && bef[i] != '\n' && i < len)
					i++;
			}

		}
		len++;
	}
	if (len > game->parse.map.width)
		game->parse.map.width = len;
	return (0);
}

int	parse_map(t_game *game, t_list **file_lines)
{
	t_list	*map_lines;
	char	*bef;
	char	*aft;

	if (game->parse.map.grid != NULL)
		return (perror_alreadydefined(E_MAP));
	if (game->parse.c.a == 0 || game->parse.f.a == 0
		|| game->parse.no == NULL || game->parse.so == NULL
		|| game->parse.we == NULL || game->parse.ea == NULL)
		return (perror_mapbeforeelements(), 1);
	map_lines = *file_lines;
	game->parse.map.height = 0;
	bef = NULL;
	while (*file_lines != NULL)
	{
		aft = NULL;
		if ((*file_lines)->next != NULL)
			aft = (*file_lines)->next->content;
		if (parse_mapline(game, (*file_lines)->content, bef, aft) == 1)
			return (1);
		bef = (*file_lines)->content;
		game->parse.map.height++;
		*file_lines = (*file_lines)->next;
	}
	// TODO: move this to a separate function
	size_t	i;
	t_list	*tmp;

	game->parse.map.grid = malloc(sizeof(char *) * (game->parse.map.height + 1));
	if (game->parse.map.grid == NULL)
		return (perror_malloc());
	game->parse.map.grid[game->parse.map.height] = NULL;
	i = 0;
	while (i < game->parse.map.height)
	{
		game->parse.map.grid[i] = (*file_lines)->content;
		tmp = (*file_lines)->next;
		ft_lstdelone(*file_lines, NULL);
		*file_lines = tmp;
		i++;
	}
	return (0);
}

static int	parse_textpath(t_game *game, t_elemfile elem, char *line)
{
	size_t	len;
	char	*path;

	while (ft_isspace(*line))
		line++;
	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
		len++;
	while (len > 0 && ft_isspace(line[len - 1]))
		len--;
	// TODO: must check if file is .xpm? Or let mlx handle it later?
	path = ft_substr(line, 0, len);
	if (path == NULL)
		return (perror_malloc());
	if (elem == E_NO)
		game->parse.no = path;
	else if (elem == E_SO)
		game->parse.so = path;
	else if (elem == E_WE)
		game->parse.we = path;
	else if (elem == E_EA)
		game->parse.ea = path;
	return (0);
}

static int	parse_color_component(char **str, uint8_t *component)
{
	int	value;

	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (perror_unexpectedchar(**str), 1);
	value = 0;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (perror_overflow(), 1);
		(*str)++;
	}
	*component = (uint8_t)value;
	while (ft_isspace(**str))
		(*str)++;
	return (0);
}

static int	parse_color(t_game *game, t_elemfile type, char *line)
{
	t_color	*color;

	if (type == E_F)
		color = &game->parse.f;
	else
		color = &game->parse.c;
	if (parse_color_component(&line, &color->r) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->g) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->b) == 1)
		return (1);
	if (*line != '\n' && *line != '\0')
		return (perror_unexpectedchar(*line), 1);
	color->a = 255;
	return (0);
}

static int	parse_header(t_game *game, t_list **file_lines, t_elemfile type)
{
	char		*line;

	// TODO: can be simplified with solved array int save_info, must do this?
	if ((type == E_C && game->parse.c.a != 0)
		|| (type == E_F && game->parse.f.a != 0)
		|| (type == E_NO && game->parse.no != NULL)
		|| (type == E_SO && game->parse.so != NULL)
		|| (type == E_WE && game->parse.we != NULL)
		|| (type == E_EA && game->parse.ea != NULL))
		return (perror_alreadydefined(type));
	line = (*file_lines)->content;
	if (type == E_C || type == E_F)
		line += 1;
	else
		line += 2;
	if (!ft_isspace(*line))
		return (perror_unexpectedchar(*line));
	if (type == E_C || type == E_F)
		return (parse_color(game, type, line));
	return (parse_textpath(game, type, line));
}

static t_elemfile	identify_element(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (E_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (E_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (E_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (E_EA);
	else if (line[0] == 'F')
		return (E_F);
	else if (line[0] == 'C')
		return (E_C);
	while (ft_isspace(*line))
		line++;
	if (line[0] == '1' || line[0] == '0')
		return (E_MAP);
	return (E_EMPTY);
}

static int	save_info(t_game *game, t_list **file_lines)
{
	t_list		*tmp;
	t_elemfile	type;

	while (*file_lines != NULL)
	{
		type = identify_element((*file_lines)->content);
		if (type == E_C || type == E_F || type == E_NO
			|| type == E_SO || type == E_WE || type == E_EA)
			if (parse_header(game, file_lines, type) == 1)
				return (ft_lstclear(file_lines, free), 1);
		else if (type == E_MAP)
		{
			if (parse_map(game, file_lines) == 1)
				return (ft_lstclear(file_lines, free), 1);
			continue ;
		}
		if (*file_lines == NULL)
			break ;
		tmp = (*file_lines)->next;
		ft_lstdelone(*file_lines, free);
		*file_lines = tmp;
	}
	return (0);
}

int	parse_game(t_game *game, int argc, char **argv)
{
	size_t	len;
	int		fd;
	t_list	*file_lines;

	if (argc != 2)
		return (perror_args());
	preinit_game(game);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		return (perror_filename());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror_open(argv[1]));
	file_lines = NULL;
	if (read_file(fd, argv[1], &file_lines) == 1)
		return (close(fd), 1);
	close(fd);
	if (save_info(game, &file_lines) == 1)
		return (1);
	if (game->parse.no == NULL || game->parse.so == NULL
		|| game->parse.we == NULL || game->parse.ea == NULL
		|| game->parse.f.a == 0 || game->parse.c.a == 0
		|| game->parse.map.grid == NULL)
		return (perror_missingelements(&game->parse), 1);
	return (0);
}
*/
