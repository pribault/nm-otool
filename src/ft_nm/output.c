/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 09:58:25 by pribault          #+#    #+#             */
/*   Updated: 2018/05/03 18:01:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void			clean_output(t_nm *nm)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (nm->buffer)
	{
		ft_memdel(&nm->buffer);
		nm->buffer_size = 0;
	}
	FD_SET(nm->pipe[0], &set);
	while (select(nm->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(nm->pipe[0], &set) &&
		(ret = read(nm->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(nm->null, &buffer, ret);
}

void			save_output(t_nm *nm)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	FD_SET(nm->pipe[0], &set);
	while (select(nm->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(nm->pipe[0], &set) &&
		(ret = read(nm->pipe[0], &buffer, sizeof(buffer))) > 0)
	{
		if (!(nm->buffer = realloc(nm->buffer, nm->buffer_size + ret)))
			ft_error(2, ERROR_ALLOCATION, NULL);
		ft_memcpy(nm->buffer + nm->buffer_size, &buffer, ret);
		nm->buffer_size += ret;
	}
}

void			print_output(t_nm *nm)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (nm->buffer)
	{
		write(nm->out, nm->buffer, nm->buffer_size);
		ft_memdel(&nm->buffer);
		nm->buffer_size = 0;
	}
	FD_SET(nm->pipe[0], &set);
	while (select(nm->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(nm->pipe[0], &set) &&
		(ret = read(nm->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(nm->out, &buffer, ret);
}

void			print_output_to(t_nm *nm, int fd)
{
	static struct timeval	time = {0, 0};
	static char				buffer[BUFF_SIZE];
	fd_set					set;
	int						ret;

	if (nm->buffer)
	{
		write(fd, nm->buffer, nm->buffer_size);
		ft_memdel(&nm->buffer);
		nm->buffer_size = 0;
	}
	FD_SET(nm->pipe[0], &set);
	while (select(nm->pipe[0] + 1, &set, NULL, NULL, &time) > 0 &&
		FD_ISSET(nm->pipe[0], &set) &&
		(ret = read(nm->pipe[0], &buffer, sizeof(buffer))) > 0)
		write(fd, &buffer, ret);
}
