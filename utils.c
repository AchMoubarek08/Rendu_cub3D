/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:48:59 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:26:26 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawmap(void *mlx, void *win, t_vars *vars)
{
	if (vars->pl_img.img)
	{
		mlx_destroy_image(mlx, vars->pl_img.img);
	}
	vars->pl_img.img = mlx_new_image(mlx, MAP_X, MAP_Y);
	vars->pl_img.addr = mlx_get_data_addr(vars->pl_img.img,
			&vars->pl_img.bits_per_pixel, &vars->pl_img.line_length,
			&vars->pl_img.endian);
	draw_rays(vars);
	mlx_put_image_to_window(mlx, win, vars->pl_img.img, 0, 0);
}

int	wall(t_vars *vars, double x, double y, int flag)
{
	int	i;
	int	j;

	i = floor((y) / 64);
	j = floor((x) / 64);
	if (flag)
	{
		if (wall(vars, x, vars->player.py, 0) == 1)
			return (1);
		if (wall(vars, vars->player.px, y, 0) == 1)
			return (1);
	}
	return (vars->parse.map[(int)i][(int)j]);
}

void	check_angle(t_rays *rays)
{
	if (rays->ra < 0)
		rays->ra += 2 * PI;
	if (rays->ra > 2 * PI)
		rays->ra -= 2 * PI;
}

void	init_ray_values(t_rays *rays, char dir, t_vars *vars)
{
	if (dir == 'u' || dir == 'd' || dir == 's')
		ray_up_or_down(rays, dir, vars);
	if (dir == 'l' || dir == 'r' || dir == 's')
		ray_lef_or_right(rays, dir, vars);
}

void	distances(t_rays *rays, t_vars *vars)
{
	if (rays->ra > PI)
		init_ray_values(rays, 'u', vars);
	if (rays->ra < PI)
		init_ray_values(rays, 'd', vars);
	if (rays->ra == 0 || rays->ra == PI)
		init_ray_values(rays, 's', vars);
	if (rays->ra > P2 && rays->ra < P3)
		init_ray_values(rays, 'l', vars);
	if (rays->ra < P2 || rays->ra > P3)
		init_ray_values(rays, 'r', vars);
	if (rays->ra == 0 || rays->ra == PI)
		init_ray_values(rays, 's', vars);
	if (rays->dist_h < rays->dist_v)
		draw_frame(rays, vars, rays->dist_h);
	else
		draw_frame(rays, vars, rays->dist_v);
}
