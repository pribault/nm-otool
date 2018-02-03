/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:39:41 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:17:04 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{0, NULL}
};

static t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{NULL, 0, {0}, NULL}
};

static t_error	g_errors[] =
{
	{ERROR_FSTAT, "cannot get stats for %s", 0},
	{ERROR_MUNMAP, "failed to unmap %s", 0},
	{ERROR_UNKNOWN_FILE_FORMAT, "'%s': unknown file format", 0},
	{0, NULL, 0}
};

void	get_file(char *file, t_nm *nm)
{
	struct stat	buff;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error(2, ERROR_FILE, file));
	nm->n++;
	if (fstat(fd, &buff) == -1)
	{
		close(fd);
		return (ft_error(2, ERROR_FSTAT, file));
	}
	nm->size = buff.st_size;
	if (!(nm->ptr = mmap(NULL, buff.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_FILE, fd, 0)))
	{
		close(fd);
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	}
	nm->opt = 0;
	if (!read_fat(nm, nm->ptr) && !read_mach(nm, nm->ptr))
		ft_error(2, ERROR_UNKNOWN_FILE_FORMAT, file);
	if (munmap(nm->ptr, buff.st_size) == -1)
		ft_error(2, ERROR_MUNMAP, file);
	close(fd);
}

void	init_nm(t_nm *nm, int argc, char **argv)
{
	ft_bzero(nm, sizeof(t_nm));
	nm->n = 0;
	ft_add_errors((t_error*)&g_errors);
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_file), nm);
}

int		main(int argc, char **argv)
{
	t_nm	nm;

	init_nm(&nm, argc, argv);
	if (!nm.n)
	{
		print_usage();
		return (1);
	}
	return (0);
}
