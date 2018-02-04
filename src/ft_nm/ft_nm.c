/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:39:41 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 17:47:53 by pribault         ###   ########.fr       */
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
	{ERROR_FILE_CORRUPTED, "'%s': file corrupted", 0},
	{0, NULL, 0}
};

void	reset_nm(t_nm *nm)
{
	ft_vector_resize(nm->syms_32, 0);
	ft_vector_resize(nm->sect_32, 0);
	ft_vector_resize(nm->syms_64, 0);
	ft_vector_resize(nm->sect_64, 0);
	clean_output(nm->out);
	nm->ptr = NULL;
	nm->stroff = 0;
	nm->size = 0;
	nm->opt = 0;
}

void	read_file(char *file, t_nm *nm)
{
	t_ret		ret;

	if ((ret = read_fat(nm, nm->ptr, file)) == RETURN_SUCCESS)
		return (print_output(nm->out));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_mach(nm, nm->ptr, file, TYPE_MACH)) == RETURN_SUCCESS)
		return (print_output(nm->out));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_ar(nm, nm->ptr, file)) == RETURN_SUCCESS)
		return (print_output(nm->out));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	ft_error(2, ERROR_UNKNOWN_FILE_FORMAT, file);
}

void	get_file(char *file, t_nm *nm)
{
	struct stat	buff;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error(2, ERROR_FILE, file));
	if (fstat(fd, &buff) == -1)
	{
		close(fd);
		return (ft_error(2, ERROR_FSTAT, file));
	}
	nm->size = buff.st_size;
	if (!(nm->ptr = mmap(NULL, buff.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_FILE, fd, 0)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	read_file(file, nm);
	if (munmap(nm->ptr, buff.st_size) == -1)
		ft_error(2, ERROR_MUNMAP, file);
	close(fd);
	reset_nm(nm);
}

void	init_nm(t_nm *nm, int argc, char **argv)
{
	ft_bzero(nm, sizeof(t_nm));
	if (!(nm->files = ft_vector_new(sizeof(char *), 0)) ||
		!(nm->syms_32 = ft_vector_new(sizeof(struct nlist), 0)) ||
		!(nm->syms_64 = ft_vector_new(sizeof(struct nlist_64), 0)) ||
		!(nm->sect_32 = ft_vector_new(sizeof(struct section), 0)) ||
		!(nm->sect_64 = ft_vector_new(sizeof(struct section_64), 0)) ||
		!(nm->out = ft_vector_new(sizeof(char *), 0)))
		ft_error(2, ERROR_ALLOCATION, NULL);
	ft_add_errors((t_error*)&g_errors);
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_default), nm);
}

int		main(int argc, char **argv)
{
	size_t	i;
	t_nm	nm;

	init_nm(&nm, argc, argv);
	if (!nm.files->n)
	{
		print_usage();
		return (1);
	}
	i = (size_t)-1;
	while (++i < nm.files->n)
		get_file(*(char**)ft_vector_get(nm.files, i), &nm);
	return (0);
}
