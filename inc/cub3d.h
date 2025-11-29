/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/29 17:24:12 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 700
# define HEIGHT 600
# define PI 3.1415926535

# define M_SIZE 200 // Mini map size
# define M_PLAYER 5 // Mini map size
# define MARGIN 0.25

# define ANGLE_FOV 66.0

# define WIN_TITLE "The best cub in the world"

# include "structs.h"

# include "mlx.h"
# include "libft.h"

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# include <X11/X.h> // X11 interface, events, masks
# include <X11/keysym.h> // XK_* (keysyms)

int			perror_malloc(void);
int			perror_open(char *filename);
int			perror_gnl(char *filename);

int			perror_texture(char *filename);

// parse

int			perror_args(void);

int			perror_filename(void);
int			perror_unexpectedchar(char unexpected);
int			perror_alreadydefined(t_elemfile elem);
int			perror_overflow(void);
int			perror_missingelements(uint8_t seen);
int			perror_emptylineinmap(void);
int			perror_emptyarg(t_elemfile elem);
int			perror_unclosedmap(void);
int			perror_multipleplayerstart(void);
int			perror_noplayerstart(void);

void		preinit_parse(t_game *game, t_parse *parse);

int			is_player_char(char c);
int			is_map_char(char c);
int			is_void_char(char c);

int			check_mapspacechar(t_game *game, size_t row, size_t col);

int			parse_header(t_game *game, char	*line, t_parse	*parse);

int			parse_map(t_game *game, t_parse *parse);

int			parse_game(t_game *game, int argc, char **argv);

// free

void		free_infile(t_game *game);
void		free_parse(t_game *game, t_parse *parse);

void		ft_destroy_image(t_game *game, t_buf *image);

void		free_end(t_game *game);

// color

t_color		color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	pack_color(int endian, t_color color);

// inits

int			init_mlx(t_game *game);
int			init_game(t_game *game);

// raycasting

void		raycasting(t_game *game);
void		steps_init(t_game *game, t_dda *dda);
void		dda_loop(t_game *game, t_dda *dda);
int			check_hit(t_game *game, t_dda *dda);
void		fpredrawing(t_game *game, t_dda *dda);
void		render_frame(t_game *game, t_dda *dda);
void		render_column(t_game *game, t_dda *dda);

// move

void		move_vector_view(int type, t_game *game);
void		lateral_transition(int type, t_game *game);

// events

int			ft_events(t_game *game);
int			ft_key_press(int keycode, t_game *game);
int			ft_key_release(int keycode, t_game *game);
int			ft_close(t_game *game);

uint32_t	get_pixel(t_buf *img, int x, int y);
void		pixel_image(t_buf *img, int x, int y, uint32_t color);
void		clear_image(t_buf *img);

// math functions

double		degrees(double grad);
double		get_delta_dist(float rdir);

// BONUS:

// Minimap
void		draw_square(t_game *game, int x, int y, uint32_t color); //1und grid
void		render_minmap(t_game *game);
void		mini_map(t_game *game);

// Functions to textures.

// Collisions





#endif
