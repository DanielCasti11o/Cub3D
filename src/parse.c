/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/31 19:33:08 by migugar2         ###   ########.fr       */
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
