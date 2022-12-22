/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:45:51 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/19 23:22:13 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	errors(int error)
{
	if (error == 1)
		ft_putstr_fd("indetifien(s) de texture invalide(s)\n", 2);
	else if (error == 2)
		ft_putstr_fd("Chemin(s) de texture invalide(s)\n", 2);
	else if (error == 3)
		ft_putstr_fd("Nombre d'indentifiens invalide\n", 2);
	else if (error == 4)
		ft_putstr_fd("fichier(s) de texture incorrect\n", 2);
	else if (error == 5)
		ft_putstr_fd("Extension de fichier invalide\n", 2);
	else if (error == 6)
		ft_putstr_fd("Couleur(s) RGB hors intervalle\n", 2);
	else if (error == 7)
		ft_putstr_fd("Couleur(s) RGB invalide\n", 2);
	else if (error == 8)
		ft_putstr_fd("Map invalide\n", 2);
	else if (error == 9)
		ft_putstr_fd("Map non fermée\n", 2);
	else if (error == 10)
		ft_putstr_fd("More or less than one player\n", 2);
	else if (error == 11)
		ft_putstr_fd("More than one argument\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

int	check_txt_path(char *path)
{
	int		i;
	int		j;
	int		fd;
	char	*filename;

	i = ft_int_strchr(path, '.');
	j = ft_int_strrchr(path, 'm');
	if (j == -1)
		errors(5);
	if (i == -1 || (path[i + 1] && path[i + 1] != '/'))
		errors(2);
	filename = ft_substr(path, i, j - i + 1);
	check_filename(filename + 2, 2);
	fd = open(filename + 2, O_RDONLY);
	if (fd == -1)
		errors(4);
	free(path);
	free(filename);
	close(fd);
	return (0);
}

void	init_pvars(t_pvars *x)
{
	x->i = 0;
	x->j = 0;
	x->tex = 0;
	x->cf = 0;
	x->tab = malloc(sizeof(char *) * 7);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
