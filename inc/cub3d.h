/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/09 11:12:04 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 700
# define HEIGHT 600
# define PI 3.1415926535

# include "structs.h"

# include "mlx.h"
# include "libft.h"

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

int		perror_malloc(void);
int		perror_open(char *filename);
int		perror_gnl(char *filename);

int		perror_args(void);
int		perror_filename(void);

// parse

int		perror_unexpectedchar(char unexpected);
int		perror_alreadydefined(t_elemfile elem);
int		perror_overflow(void);
int		perror_missingelements(uint8_t seen);
int		perror_emptylineinmap(void);
int		perror_emptyarg(t_elemfile elem);
int		perror_unclosedmap(void);
int		perror_multipleplayerstart(void);
int		perror_noplayerstart(void);

void	free_infile(t_game *game);
void	free_parse(t_game *game, t_parse *parse);

void	free_end(t_game *game);

t_color	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void	preinit_parse(t_game *game, t_parse *parse);

int		is_player_char(char c);
int		is_map_char(char c);
int		is_void_char(char c);

int		check_mapspacechar(t_game *game, size_t row, size_t col);

int		parse_header(t_game *game, char	*line, t_parse	*parse);

int		parse_map(t_game *game, t_parse *parse);

int		parse_game(t_game *game, int argc, char **argv);

// Inits

void	init_player(t_game *game);
void	init_window(t_game *game);

// RayCasting

void	raycasting(t_game *game, t_vec dir);
void	steps(t_dda dda, t_game *game, t_vec dir);
void	dda_loop(t_game *game, t_vec dir, t_dda dda);
int		check_hit(t_game *game, t_vec dir, t_dda dda);
void	fpredrawing(t_game *game, t_vec dir, t_dda dda);
void	limdrawing(t_game *game, t_vec dir, t_dda dda);


// Events

int		ft_events(t_game *game);
int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_game *game);
void	pixel_image(t_img *img, int x, int y, double color);
void	clear_image(t_img *img);

// Math functions

double	degrees(double grad);

#endif
