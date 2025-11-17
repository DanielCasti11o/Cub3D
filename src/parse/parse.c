/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/17 20:52:07 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	push_linemap(t_parse *parse, char *line)
{
	t_list	*new_node;

	new_node = ft_lstnew(line);
	if (new_node == NULL)
		return (perror_malloc());
	if (parse->head_map == NULL)
		parse->head_map = new_node;
	else
		parse->tail_map->next = new_node;
	parse->tail_map = new_node;
	return (0);
}

static int	save_linemap(t_game *game, t_parse *parse, char *line, ssize_t len)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (len == 0 || line[i] == '\0' || line[i] == '\n')
	{
		free(line);
		parse->state = SP_DONE;
		return (0);
	}
	else if (parse->state == SP_DONE)
		return (perror_emptylineinmap(), 1);
	if (push_linemap(parse, line) == 1)
		return (1);
	while (len > 0 && (ft_isspace(line[len - 1]) || line[len - 1] == '\n'))
		len--;
	if (parse->first_v_char == -1 || i < (size_t)parse->first_v_char)
		parse->first_v_char = i;
	if (len > parse->last_v_char)
		parse->last_v_char = len;
	return (game->map.height++, 0);
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
			if (save_linemap(game, parse, line, bytes_read) == 1)
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
	preinit_parse(game, &parse);
	if (parse_stream(game, &parse, fd, argv[1]) == 1)
		return (close(fd), free_parse(game, &parse), 1);
	close(fd);
	if (parse_map(game, &parse) == 1)
		return (free_parse(game, &parse), 1);
	if (parse.seen != (E_NO | E_SO | E_WE | E_EA | E_F | E_C | E_MAP))
		return (perror_missingelements(parse.seen),
			free_parse(game, &parse), 1);
	return (0);
}
