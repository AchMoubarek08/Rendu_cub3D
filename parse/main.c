/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:50:18 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/21 00:09:02 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	fill_cf_colors(t_parse *data, char *line, int x)
{
	char	**colors;
	int		i;
	int		r;
	int		g;
	int		b;

	colors = ft_split(line, ',');
	i = 0;
	while (colors[i])
	{
		remove_spaces(colors[i]);
		i++;
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (x == 1)
		data->cell = (r << 16) + (g << 8) + b;
	else if (x == 2)
		data->floor = (r << 16) + (g << 8) + b;
	ft_free_tab(colors);
}

void	fill_iden(t_parse *data, char **file)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (file[i])
	{
		start = ft_int_strchr(file[i], '.');
		end = ft_int_strrchr(file[i], 'm');
		if (is_identifier(file, i) == 1)
			data->no = ft_substr(file[i], start, end - start + 1);
		else if (is_identifier(file, i) == 2)
			data->so = ft_substr(file[i], start, end - start + 1);
		else if (is_identifier(file, i) == 3)
			data->we = ft_substr(file[i], start, end - start + 1);
		else if (is_identifier(file, i) == 4)
			data->ea = ft_substr(file[i], start, end - start + 1);
		else if (is_cellingfloor(file, i) == 1)
			fill_cf_colors(data, file[i] + 1, 1);
		else if (is_cellingfloor(file, i) == 2)
			fill_cf_colors(data, file [i] + 1, 2);
		i++;
	}
}

void	get_height_width(t_parse *data, char **map)
{
	int	i;

	i = 0;
	while (map[i] && is_mapline(map, i) && strcmp(map[i], ""))
	{
		if (ft_strlen(map[i]) > data->width)
			data->width = ft_strlen(map[i]);
		i++;
	}
	data->height = i;
}

void	fill_file(char **file, char **av)
{	
	int		i;
	int		fd;
	char	*line;
	char	*tmp;

	i = 0;
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	tmp = line;
	while (line)
	{
		line = extract_newline(line);
		file[i] = line;
		ft_free(&tmp);
		line = get_next_line(fd);
		tmp = line;
		i++;
	}
	close(fd);
	ft_free(&tmp);
	file[i] = NULL;
}

int	parse_map(int argc, char **argv, t_parse *data)
{
	char	**file;
	char	**iden;
	char	**map;

	if (argc != 2)
		errors(11);
	if (argv[1])
		check_filename(argv[1], 1);
	file = malloc(sizeof(char *) * 200);
	fill_file(file, argv);
	iden = collect_identifiers(file);
	check_iden(iden);
	map = collect_map(file);
	check_map(map);
	fill_iden(data, iden);
	fill_map(data, map);
	ft_free_tab(file);
	ft_free_tab(map);
	free(iden);
	return (0);
}
