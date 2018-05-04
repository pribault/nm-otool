/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reduce_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 18:15:43 by pribault          #+#    #+#             */
/*   Updated: 2018/04/01 16:58:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*get_elem(char *elem)
{
	static char	buff[128];
	uint64_t	i;

	i = 0;
	while (elem[i] && elem[i] != '/' && i < sizeof(buff) - 1)
	{
		buff[i] = elem[i];
		i++;
	}
	buff[i] = '\0';
	return ((char*)&buff);
}

static uint64_t	get_prev(char *path, uint64_t i)
{
	if (i < 2)
		return ((uint64_t)-1);
	i -= 2;
	while (i != (uint64_t)-1 && path[i] != '/')
		i--;
	return ((path[i] == '/') ? i + 1 : (uint64_t)-1);
}

static uint64_t	reduce_superior(char *path, uint64_t prev, uint64_t i)
{
	if (path[i + 2] == '/')
		ft_memcpy(&path[prev], &path[i + 3], ft_strlen(&path[i + 3]) + 1);
	else
		path[prev] = '\0';
	return (prev);
}

static void		reduce_current(char *path)
{
	if (path[1] == '/')
		ft_memcpy(path, &path[2], ft_strlen(&path[2]) + 1);
	else
		path[0] = '\0';
}

char			*ft_reduce_path(char *path)
{
	char		*elem;
	uint64_t	prev;
	uint64_t	i;

	i = (uint64_t)0;
	while (path[i])
	{
		while (path[i] == '/')
			if (i && path[i - 1] == '/')
				ft_memcpy(&path[i], &path[i + 1], ft_strlen(&path[i + 1]) + 1);
			else
				i++;
		if (path[i] != '/')
		{
			if (!ft_strcmp((elem = get_elem(&path[i])), "..") &&
				(prev = get_prev(path, i)) != (uint64_t)-1)
				i = reduce_superior(path, prev, i);
			else if (!ft_strcmp(elem, "."))
				reduce_current(&path[i]);
			else
				while (path[i] && path[i] != '/')
					i++;
		}
	}
	return (path);
}
