/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/28 20:25:55 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 700
# define HEIGHT 600
# define PI 3.1415926535

# include <string.h>
# include "mlx.h"
# include <stdlib.h>
# include "libft.h"
# include <stdbool.h>
# include <math.h>
# include <stdio.h>

// This structure draws everything in an invisible buffer
//  that stores all the information about everything that will later
// be drawn on the screen, thus avoiding flickering.

// < This concept is called "Double Buffering." >
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_pos
{
	float	x;
	float	y;
	float	to_x;
	float	to_y;
	float	ray_x;
	float	ray_y;
	bool	is_inside; // algorithm bsp rectangle adaptation
	int		value; // key in map
}	t_pos;

typedef struct s_textures
{
	void	*wall;
	void	*flood;
	void	*door;
	void	*flash; // Is opcional.
	void	*sphere; // Ray tracing
	void	*mini_map;
}	t_texture;

typedef struct s_vision
{
	long	triangle; // triangle of vision in the map
	bool	sphere_inside; // bsp triangule vision
	float	angle;
}	t_vision;

typedef struct s_keys
{
	int	a;
	int	w;
	int	s;
	int	d;
	int	right;
	int	left;
	int	up;
	int	down;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_pos		pos;
	t_vision	vision;
	t_texture	textures;
	t_keys		keys;
	t_img		img_w;
}	t_game;

// int	parse(void);
void	init_window(t_game *game);
int		ft_events(t_game *game);
void	loop_ray(t_game *game);
int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_game *game);
void	loop_ray(t_game *game);
void	pixel_image(t_img *img, int x, int y, double color);
void	clear_image(t_img *img);

// Math functions
double	degrees(double grad);

#endif
