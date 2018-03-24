/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:42:49 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 16:13:00 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_short_flag	g_short_flags[] =
{
	{'h', (void*)&print_usage},
	{'d', (void*)&set_debug},
	{0, NULL}
};

t_long_flag	g_long_flags[] =
{
	{"help", 0, {0}, (void*)&print_usage},
	{"debug", 0, {0}, (void*)&set_debug},
	{NULL, 0, {0}, NULL}
};

t_error		g_errors[] =
{
	{ERROR_FSTAT, "cannot get stats for %s", 0},
	{ERROR_MUNMAP, "failed to munmap %s", 0},
	{ERROR_UNKNOWN_FILE_FORMAT, "'%s': unknown file format", 0},
	{ERROR_FILE_CORRUPTED, "'%s': file corrupted", 0},
	{ERROR_ON_FD, "error setting file descriptors", ERROR_EXIT},
	{ERROR_EMPTY_FILE, "%s empty", 0},
	{0, NULL, 0}
};

void	reset_otool(t_otool *otool)
{
	otool->ptr = NULL;
	otool->size = 0;
	otool->opt &= ~(MACH_ENDIAN | FAT_ENDIAN);
}

void	read_file(char *file, t_otool *otool)
{
	t_ret		ret;

	if ((ret = read_fat(otool, otool->ptr, file)) == RETURN_SUCCESS)
		return (print_output(otool));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_mach(otool, otool->ptr, file, TYPE_MACH)) == RETURN_SUCCESS)
		return (print_output(otool));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	if ((ret = read_ar(otool, otool->ptr, file)) == RETURN_SUCCESS)
		return (print_output(otool));
	if (ret == RETURN_FILE_CORRUPTED)
		return (ft_error(2, ERROR_FILE_CORRUPTED, file));
	ft_error(2, ERROR_UNKNOWN_FILE_FORMAT, file);
}

void	get_file(char *file, t_otool *otool)
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
	otool->size = buff.st_size;
	if (!(otool->ptr = mmap(NULL, buff.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_FILE, fd, 0)))
		return (ft_error(2, ERROR_ALLOCATION, NULL));
	read_file(file, otool);
	if (munmap(otool->ptr, buff.st_size) == -1)
		ft_error(2, ERROR_MUNMAP, file);
	close(fd);
	reset_otool(otool);
}

void	init_otool(t_otool *otool, int argc, char **argv)
{
	ft_bzero(otool, sizeof(t_otool));
	ft_vector_init(&otool->files, sizeof(char*));
	ft_add_errors((t_error*)&g_errors);
	ft_get_flags(argc, argv, ft_get_flag_array((t_short_flag*)&g_short_flags,
	(t_long_flag*)&g_long_flags, (void*)&get_default), otool);
	if ((otool->out = open("/dev/fd/1", O_WRONLY)) == -1 ||
		(otool->null = open("/dev/null", O_WRONLY)) == -1 ||
		pipe(otool->pipe) == -1 || close(1) == -1 ||
		dup2(otool->pipe[1], 1) == -1)
		ft_error(2, ERROR_ON_FD, NULL);
	ft_vector_init(&otool->segment_32, sizeof(struct segment_command*));
	ft_vector_init(&otool->segment_64, sizeof(struct segment_command_64*));
}

int		main(int argc, char **argv)
{
	static char	*default_file = "a.out";
	size_t		i;
	t_otool		otool;

	init_otool(&otool, argc, argv);
	if (!otool.files.n)
		ft_vector_add(&otool.files, &default_file);
	i = (size_t)-1;
	while (++i < otool.files.n)
		get_file(*(char**)ft_vector_get(&otool.files, i), &otool);
	return (0);
}
