/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 22:48:23 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/20 01:09:03 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CUB3D_PARSE_H
# define CUB3D_PARSE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "gnl/get_next_line.h"

typedef struct s_pvars
{
	int		i;
	int		tex;
	int		cf;
	char	**tab;
	int		j;
}				t_pvars;

typedef struct s_parse
{
	int		cell;
	int		floor;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		**map;
	int		width;
	int		height;
	int		x;
	int		y;
	enum
	{
		N,
		S,
		E,
		W
	}	e_dir;
}	t_parse;

int		is_digit(char c);
int		str_is_space(char *str);
int		str_is_newline(char *str);
char	*extract_newline(char *str);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_int_strrchr(const char *s, int c);
void	errors(int error);
void	ft_putstr_fd(char *s, int fd);
void	print_array(char **array);
char	*remove_spaces(char *colors);

void	check_filename(char *str, int ex);
char	**collect_identifiers(char **file);
int		check_iden(char **tab);
char	**collect_map(char **file);
int		is_mapline(char **file, int i);
int		is_identifier(char **file, int i);
int		is_cellingfloor(char **file, int i);
char	*ft_free(char **lost);
void	ft_free_tab(char **tab);
int		parse_file(int argc, char **argv, t_parse *data);
int		check_map(char **map);
void	fill_map(t_parse *data, char **map);
int		str_is_digit(char *str);
int		in_range(char *str);
int		check_txt_path(char *path);
int		there_is_zero(char **map, int i);
void	skip_identifiers(char **file, int *i);
int		is_mapchar(char c);
void	init_pvars(t_pvars *x);
int		parse_map(int argc, char **argv, t_parse *data);
int		collect_iden(t_pvars *x, char **file);
void	get_height_width(t_parse *data, char **map);

#endif