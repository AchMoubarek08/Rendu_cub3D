/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:47:13 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:26:12 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_frame	*init_frame(t_vars *vars, t_rays *rays, float dist)
{
	t_frame	*frame;

	frame = (t_frame *)malloc(sizeof(t_frame));
	frame->dist = dist;
	frame->dist = frame->dist * cos(vars->player.pa - rays->ra);
	frame->lineh = (64 * MAP_Y * tan(45 * DR)) / frame->dist;
	frame->ofsset = (MAP_Y - frame->lineh) / 2;
	if (frame->lineh > MAP_Y)
		frame->ofsset = 0;
	if (rays->dist_v > rays->dist_h)
		frame->offsetx = (int)(rays->h_rx) % 64;
	else
		frame->offsetx = (int)(rays->v_ry) % 64;
	return (frame);
}

void	draw_celling(t_data *img, int x, int y, int color)
{
	int	dy;

	dy = 0;
	while (dy < y)
	{
		my_mlx_pixel_put(img, x, dy, color);
		dy++;
	}
}

void	draw_floor(t_data *img, int x, int y, int color)
{
	int	dy;

	dy = y;
	while (dy > 0 && dy < MAP_Y)
	{
		my_mlx_pixel_put(img, x, dy, color);
		dy++;
	}
}

void	draw_wall(t_vars *vars, t_rays *rays, t_frame *frame)
{
	int	dy;

	dy = 0;
	while (dy < frame->lineh && dy < MAP_Y)
	{
		frame->distance = (frame->ofsset + dy
				+ ((int)frame->lineh / 2) - (MAP_Y / 2));
		frame->offsety = frame->distance * ((float)64 / (int)frame->lineh);
		put_it(vars, rays, frame, dy);
		dy++;
	}
}

void	draw_frame(t_rays *rays, t_vars *vars, float dist)
{
	int			dx;
	t_frame		*frame;

	frame = init_frame(vars, rays, dist);
	draw_celling(&vars->pl_img, rays->num_r, frame->ofsset, vars->parse.cell);
	draw_wall(vars, rays, frame);
	draw_floor(&vars->pl_img, rays->num_r,
		frame->ofsset + frame->lineh, vars->parse.floor);
	free(frame);
}
