/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:50:13 by pribault          #+#    #+#             */
/*   Updated: 2017/11/04 11:24:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl_stack		*get_stack(t_vector *stacks, int fd)
{
	t_gnl_stack	*stack;
	t_gnl_stack	new;
	size_t		i;

	i = 0;
	while (i < stacks->n && (stack = ft_vector_get(stacks, i++)))
		if (stack->fd == fd)
			return (stack);
	new.fd = fd;
	new.line[0] = '\0';
	ft_vector_add(stacks, &new);
	if ((stack = ft_vector_get(stacks, i)))
		return (stack);
	return (NULL);
}

static int		alloc(int fd, char **line, char *b)
{
	size_t	len;
	char	*tmp;
	int		r;

	r = 1;
	len = ft_strlen(*line);
	if (!ft_strchr(b, '\n'))
	{
		while ((r = read(fd, b, BUFF_SIZE)) &&
		!(b[r] = '\0') && !ft_strchr(b, '\n'))
		{
			*line = realloc(*line, len + r + 1);
			ft_memcpy(*line + len, b, r + 1);
			len += r;
		}
	}
	if (r < 0)
		return (-1);
	*line = realloc(*line, len + BUFF_SIZE + 1);
	ft_memcpy(*line + len, b, BUFF_SIZE + 1);
	if ((tmp = ft_strchr(*line, '\n')))
		*tmp = '\0';
	return (r);
}

void			copy_in_buffer(char *buffer, char *s)
{
	size_t	len;

	len = ft_strlen(s);
	ft_memcpy(buffer, s, len);
	buffer[len] = '\0';
}

int				ft_get_next_line(int const fd, char **line)
{
	static t_vector	*stacks = NULL;
	t_gnl_stack		*stack;
	char			buffer[BUFF_SIZE + 1];
	int				r;

	if ((!stacks && !(stacks = ft_vector_new(sizeof(t_gnl_stack), 0))) ||
	fd < 0 || read(fd, &r, 0) == -1 || !(stack = get_stack(stacks, fd)))
		return (-1);
	if (stack->line[0])
	{
		*line = ft_strdup((char*)&stack->line);
		stack->line[0] = '\0';
	}
	else
		*line = ft_strdup("");
	ft_memcpy(&buffer, *line, ft_strlen(*line) + 1);
	if ((r = alloc(fd, line, buffer)) < 0)
		return (-1);
	if (ft_strchr(buffer, '\n') && ft_strlen(buffer))
		copy_in_buffer(stack->line, ft_strchr(buffer, '\n') + 1);
	if (r == 0 && !ft_strlen(*line))
		return (0);
	return (1);
}
