/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:02:29 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:34:58 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "parse/cub3d_parse.h"
# include "parse/gnl/get_next_line.h"

# define PI 3.14159265358979323846
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define MAP_X 1200
# define MAP_Y 800
# define DR 0.01745329251
# define P2 1.57079632679
# define P3 4.71238898038
# define SO 0
# define NO 1
# define EA 2
# define WE 3

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_rays
{
	int		num_r;
	float	v_rx;
	float	v_ry;
	float	h_ry;
	float	h_rx;
	float	ra;
	float	r_xo;
	float	r_yo;
	float	dist_h;
	float	dist_v;
}	t_rays;

typedef struct s_frame
{
	float	lineh;
	float	dist;
	float	distance;
	float	ofsset;
	int		offsetx;
	float	offsety;
}	t_frame;

typedef struct s_player
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		aleft;
	int		aright;
	float	px;
	float	py;
	float	pa;
	float	pdx;
	float	pdy;
}				t_player;

typedef struct s_texture
{
	char	*file;
	t_data	tex_img;
	int		*data;
	int		*dir;
	int		img_width;
	int		img_height;
}	t_texture;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		pl_img;
	int			map[12][16];
	t_texture	textures[4];
	t_player	player;
	t_parse		parse;
}				t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	drawplayer(t_vars *vars);
void	drawmap(void *mlx, void *win, t_vars *vars);
void	draw_rays(t_vars *vars);
void	move(t_vars *vars);
int		render_next_frame(t_vars *vars);
int		update(t_vars *vars);
int		init_textures(t_vars *vars, int Dir, char *name);
void	check_angle(t_rays *rays);
void	initplayer(t_vars *vars);
int		wall(t_vars *vars, double x, double y, int flag);
void	init_ray_values(t_rays *rays, char dir, t_vars *vars);
void	draw_frame(t_rays *rays, t_vars *vars, float dist);
void	ray_up_or_down(t_rays *rays, char dir, t_vars *vars);
void	ray_lef_or_right(t_rays *rays, char dir, t_vars *vars);
void	distances(t_rays *rays, t_vars *vars);
void	put_it(t_vars *vars, t_rays *rays, t_frame *frame, int dy);
#endif