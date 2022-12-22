/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:45:04 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:22:47 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_rays(t_vars *vars)
{
	t_rays	*rays;

	rays = (t_rays *)malloc(sizeof(t_rays));
	rays->ra = vars->player.pa - (30 * DR);
	check_angle(rays);
	rays->num_r = 0;
	while (rays->num_r < MAP_X)
	{
		distances(rays, vars);
		rays->ra += DR / (MAP_X / 60);
		check_angle(rays);
		rays->num_r++;
	}
	free(rays);
}

void	search_h_inter(t_rays *rays, t_vars *vars, int x)
{
	int		mx;
	int		my;
	int		dof;

	dof = x;
	while (dof < vars->parse.height)
	{
		mx = (int)(rays->h_rx) / 64;
		my = (int)(rays->h_ry) / 64;
		if (abs(my) < vars->parse.height && abs(mx)
			< vars->parse.width && vars->parse.map[abs(my)][abs(mx)] == 1)
			dof = vars->parse.height;
		else
		{
			rays->h_rx += rays->r_xo;
			rays->h_ry += rays->r_yo;
			dof += 1;
		}
	}
	rays->dist_h = fabs(fabs(vars->player.py - rays->h_ry) / sin(rays->ra));
}

void	search_v_inter(t_rays *rays, t_vars *vars, int x)
{
	int		mx;
	int		my;
	int		dof;

	dof = x;
	while (dof < vars->parse.width)
	{
		mx = (int)(rays->v_rx) / 64;
		my = (int)(rays->v_ry) / 64;
		if (abs(my) < vars->parse.height && abs(mx)
			< vars->parse.width && vars->parse.map[abs(my)][abs(mx)] == 1)
			dof = vars->parse.width;
		else
		{
			rays->v_rx += rays->r_xo;
			rays->v_ry += rays->r_yo;
			dof += 1;
		}
	}
	rays->dist_v = fabs(fabs(vars->player.py - rays->v_ry) / sin(rays->ra));
}

void	ray_lef_or_right(t_rays *rays, char dir, t_vars *vars)
{
	float	atan;

	atan = -tan(rays->ra);
	if (dir == 'l')
	{
		rays->v_rx = ((int)vars->player.px
				- ((int)vars->player.px % 64)) - 0.01;
		rays->r_xo = -64;
	}
	else
	{
		rays->v_rx = ((int)vars->player.px - ((int)vars->player.px % 64)) + 64;
		rays->r_xo = 64;
	}
	rays->v_ry = (vars->player.px - rays->v_rx) * atan + vars->player.py;
	rays->r_yo = -rays->r_xo * atan;
	if (dir == 's')
	{
		rays->v_rx = vars->player.px;
		rays->v_ry = vars->player.py;
		search_v_inter(rays, vars, vars->parse.width);
		return ;
	}
	search_v_inter(rays, vars, 0);
}

void	ray_up_or_down(t_rays *rays, char dir, t_vars *vars)
{
	float	atan;

	atan = -1 / tan(rays->ra);
	if (dir == 'u')
	{
		rays->h_ry = ((int)vars->player.py
				- ((int)vars->player.py % 64)) - 0.01;
		rays->r_yo = -64;
	}
	else
	{
		rays->h_ry = ((int)vars->player.py - ((int)vars->player.py % 64)) + 64;
		rays->r_yo = 64;
	}
	rays->h_rx = (vars->player.py - rays->h_ry) * atan + vars->player.px;
	rays->r_xo = -rays->r_yo * atan;
	if (dir == 's')
	{
		rays->h_rx = vars->player.px;
		rays->h_ry = vars->player.py;
		search_h_inter(rays, vars, vars->parse.height);
		return ;
	}
	search_h_inter(rays, vars, 0);
}
