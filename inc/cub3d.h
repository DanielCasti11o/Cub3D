/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/14 16:49:24 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 700
# define HEIGHT 600

# include <string.h>
# include "../libs/minilibx-linux/mlx.h"
# include <stdlib.h>
# include "../libs/libft_bonus/libft.h"
# include <stdbool.h>
# include <math.h>
# include <stdio.h>

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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_pos		pos;
	t_vision	vision;
	t_texture	textures;
}	t_game;

// int	parse(void);
void	init_window(t_game *game);

#endif
