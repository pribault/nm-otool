/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 16:06:11 by pribault          #+#    #+#             */
/*   Updated: 2017/10/11 22:46:30 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_get_all_lines(int fd, char **str)
{
	char	buffer[BUFF_SIZE];
	size_t	size;
	int		r;

	if (fd < 0 || read(fd, buffer, 0) == -1)
		return (-1);
	size = 0;
	*str = NULL;
	while ((r = read(fd, buffer, BUFF_SIZE)))
	{
		*str = realloc(*str, size + r);
		ft_memcpy(*str + size, buffer, r);
		size += r;
	}
	*str = realloc(*str, size + 1);
	(*str)[size] = '\0';
	return (1);
}
