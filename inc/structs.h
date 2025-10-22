/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:43:02 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/22 15:38:41 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> // bool
# include <stdint.h> // int, uint types

typedef enum e_elemfile
{
	E_NO,
	E_SO,
	E_WE,
	E_EA,
	E_F,
	E_C,
	E_INVALID
}	t_elemfile;

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
}	t_game;

#endif
