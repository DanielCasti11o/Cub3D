/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/21 18:13:03 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_game(t_game *game, int argc, char **argv)
{
	size_t	len;
	int		fd;

	if (argc != 2)
		return (perror_args());
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		return (perror_filename());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror_open(argv[1]));
	close(fd);
	return (0);
	(void)game;
}
