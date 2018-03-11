/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:42:45 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 19:31:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			clean_output(t_otool *otool)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (otool->buffer)
	{
		ft_memdel(&otool->buffer);
		otool->buffer_size = 0;
	}
	FD_SET(otool->pipe[0], &set);
	while (select(otool->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(otool->pipe[0], &set) &&
		(ret = read(otool->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(otool->null, &buffer, ret);
}

void			save_output(t_otool *otool)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	FD_SET(otool->pipe[0], &set);
	while (select(otool->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(otool->pipe[0], &set) &&
		(ret = read(otool->pipe[0], &buffer, sizeof(buffer))) > 0)
	{
		if (!(otool->buffer = realloc(otool->buffer, otool->buffer_size + ret)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(otool->buffer + otool->buffer_size, &buffer, ret);
		otool->buffer_size += ret;
	}
}

void			print_output(t_otool *otool)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (otool->buffer)
	{
		write(otool->out, otool->buffer, otool->buffer_size);
		ft_memdel(&otool->buffer);
		otool->buffer_size = 0;
	}
	FD_SET(otool->pipe[0], &set);
	while (select(otool->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(otool->pipe[0], &set) &&
		(ret = read(otool->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(otool->out, &buffer, ret);
}

void			print_output_to(t_otool *otool, int fd)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (otool->buffer)
	{
		write(fd, otool->buffer, otool->buffer_size);
		ft_memdel(&otool->buffer);
		otool->buffer_size = 0;
	}
	FD_SET(otool->pipe[0], &set);
	while (select(otool->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(otool->pipe[0], &set) &&
		(ret = read(otool->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(fd, &buffer, ret);
}
