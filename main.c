/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 02:42:07 by hlachkar          #+#    #+#             */
/*   Updated: 2022/12/22 02:27:41 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_it(t_vars *vars, t_rays *rays, t_frame *frame, int dy)
{
	if (rays->dist_v < rays->dist_h)
	{
		if (rays->ra > P2 && rays->ra < P3)
			my_mlx_pixel_put(&vars->pl_img, rays->num_r,
				frame->ofsset + dy, vars->textures[WE].data
			[(int)(((int)frame->offsety) * 64 + frame->offsetx)]);
		else
			my_mlx_pixel_put(&vars->pl_img, rays->num_r, frame->ofsset
				+ dy, vars->textures[EA].data[(int)
				(((int)frame->offsety) * 64 + frame->offsetx)]);
	}
	else
	{
		if (rays->ra > PI)
			my_mlx_pixel_put(&vars->pl_img, rays->num_r, frame->ofsset
				+ dy, vars->textures[SO].data[(int)
				(((int)frame->offsety) * 64 + frame->offsetx)]);
		else
			my_mlx_pixel_put(&vars->pl_img, rays->num_r, frame->ofsset
				+ dy, vars->textures[NO].data[(int)
				(((int)frame->offsety) * 64 + frame->offsetx)]);
	}
}

void	initplayer(t_vars *vars)
{
	vars->pl_img.img = NULL;
	vars->player.py = 64 * vars->parse.y + 32;
	vars->player.px = 64 * vars->parse.x + 32;
	vars->player.pa = vars->parse.e_dir * (P3);
	vars->player.down = 0;
	vars->player.up = 0;
	vars->player.left = 0;
	vars->player.right = 0;
	vars->player.aleft = 0;
	vars->player.aright = 0;
	vars->player.pdx = cos(vars->player.pa) * 3;
	vars->player.pdy = sin(vars->player.pa) * 3;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

int	init_textures(t_vars *vars, int Dir, char *name)
{
	vars->textures[Dir].file = name;
	vars->textures[Dir].tex_img.img = mlx_xpm_file_to_image(
			vars->mlx, vars->textures[Dir].file,
			&vars->textures[Dir].img_width, &vars->textures[Dir].img_height);
	if (!vars->textures[Dir].tex_img.img)
		errors(11);
	vars->textures[Dir].data = (int *)mlx_get_data_addr(
			vars->textures[Dir].tex_img.img,
			&vars->textures[Dir].tex_img.bits_per_pixel,
			&vars->textures[Dir].tex_img.line_length,
			&vars->textures[Dir].tex_img.endian);
	return (1);
}

int	main(int ac, char *av[])
{
	t_vars	vars;
	t_parse	*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	parse_map(ac, av, parse);
	vars.parse = *parse;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, MAP_X, MAP_Y, "Cub3d");
	initplayer(&vars);
	init_textures(&vars, NO, parse->no);
	init_textures(&vars, SO, parse->so);
	init_textures(&vars, WE, parse->we);
	init_textures(&vars, EA, parse->ea);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
