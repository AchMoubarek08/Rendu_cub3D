/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:20:46 by amoubare          #+#    #+#             */
/*   Updated: 2022/10/30 23:59:17 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	nadi(char **stock, char **ligne)
{
	char	*temp;
	int		x;

	x = ft_int_strchr(*stock, '\n') + 1;
	*ligne = ft_substr(*stock, 0, x);
	temp = *stock;
	*stock = ft_substr(*stock, x, ft_strlen(*stock));
	free(temp);
}

char	*ft_free(char **lost)
{
	if (*lost)
		free(*lost);
	*lost = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			i;
	char		buff[20 + 1];
	char		*ligne;
	static char	*stock;
	char		*temp;

	while (ft_int_strchr(stock, '\n') == -1)
	{
		i = read(fd, buff, 20);
		if (i == 0 || i == -1)
		{
			if (stock && stock[0] == '\0')
				ft_free(&stock);
			ligne = stock;
			stock = NULL;
			return (ligne);
		}
		buff[i] = '\0';
		temp = stock;
		stock = ft_strjoin(stock, buff);
		ft_free(&temp);
	}
	nadi(&stock, &ligne);
	return (ligne);
}
