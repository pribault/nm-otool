/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:39:41 by pribault          #+#    #+#             */
/*   Updated: 2018/05/04 17:40:03 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'d', (void*)&set_debug},
	{'p', (void*)&set_no_sort},
	{'r', (void*)&set_reverse},
	{'n', (void*)&set_numeric_sort},
	{'u', (void*)&set_only_undefined},
	{'U', (void*)&set_no_undefined},
	{'g', (void*)&set_only_global},
	{0, NULL}
};

t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{"debug", 0, {0}, (void*)&set_debug},
	{"nosort", 0, {0}, (void*)set_no_sort},
	{"reverse", 0, {0}, (void*)&set_reverse},
	{"numeric", 0, {0}, (void*)&set_numeric_sort},
	{NULL, 0, {0}, NULL}
};

t_error		g_errors[] =
{
	{ERROR_FSTAT, "cannot get stats for %s", 0},
	{ERROR_MUNMAP, "failed to unmap %s", 0},
	{ERROR_UNKNOWN_FILE_FORMAT, "'%s': unknown file format", 0},
	{ERROR_FILE_CORRUPTED, "'%s': file corrupted", 0},
	{ERROR_ON_FD, "error setting file descriptors", ERROR_EXIT},
	{ERROR_EMPTY_FILE, "%s empty", 0},
	{ERROR_GETTING_ARCH, "cannot get arch", ERROR_EXIT},
	{0, NULL, 0}
};

void	reset_nm(t_nm *nm)
{
	ft_vector_resize(&nm->syms_32, 0);
	ft_vector_resize(&nm->sect_32, 0);
	ft_vector_resize(&nm->syms_64, 0);
	ft_vector_resize(&nm->sect_64, 0);
	nm->ptr = NULL;
	nm->stroff = 0;
	nm->size = 0;
	nm->opt &= ~(MACH_ENDIAN | FAT_ENDIAN | LOCAL_ARCH);
}

void	read_file(char *file, t_nm *nm)
{
	t_ret		ret;

	if ((ret = read_fat(nm, nm->ptr, file)) == RETURN_SUCCESS)
		return (print_output(nm));
	else
		clean_output(nm);
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_mach(nm, nm->ptr, file, TYPE_MACH)) == RETURN_SUCCESS)
		return (print_output(nm));
	else
		clean_output(nm);
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_ar(nm, nm->ptr, file)) == RETURN_SUCCESS)
		return (print_output(nm));
	else
		clean_output(nm);
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
	if (!buff.st_size)
		return (ft_error(2, ERROR_EMPTY_FILE, file));
	nm->size = buff.st_size;
	if ((nm->ptr = mmap(NULL, buff.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_FILE, fd, 0)) == MAP_FAILED)
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
	ft_vector_init(&nm->files, ALLOC_MALLOC, sizeof(char*));
	ft_vector_init(&nm->syms_32, ALLOC_MALLOC, sizeof(struct nlist));
	ft_vector_init(&nm->syms_64, ALLOC_MALLOC, sizeof(struct nlist_64));
	ft_vector_init(&nm->sect_32, ALLOC_MALLOC, sizeof(struct section));
	ft_vector_init(&nm->sect_64, ALLOC_MALLOC, sizeof(struct section_64));
	ft_add_errors((t_error*)&g_errors);
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_default), nm);
	if ((nm->out = open("/dev/fd/1", O_WRONLY)) == -1 ||
		(nm->null = open("/dev/null", O_WRONLY)) == -1 ||
		pipe(nm->pipe) == -1 || close(1) == -1 ||
		dup2(nm->pipe[1], 1) == -1)
		ft_error(2, ERROR_ON_FD, NULL);
}

int		main(int argc, char **argv)
{
	static char	*default_file = "a.out";
	size_t		i;
	t_nm		nm;

	init_nm(&nm, argc, argv);
	if (!nm.files.n)
		ft_vector_add(&nm.files, &default_file);
	i = (size_t)-1;
	while (++i < nm.files.n)
		get_file(*(char**)ft_vector_get(&nm.files, i), &nm);
	return (0);
}
