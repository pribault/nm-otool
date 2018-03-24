/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:51:52 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 16:01:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_ret	verif_segment_32(t_otool *otool, void *ptr)
{
	struct segment_command	*segment;
	struct section			*section;
	uint64_t				i;

	if (!(segment = get_segment_command(otool, ptr)))
		return (0);
	i = (uint64_t)-1;
	while (++i < segment->nsects)
		if (!(section = get_section(otool, ptr + sizeof(struct segment_command)
			+ i * sizeof(struct section))) ||
			!get_str(otool, (char*)&section->sectname) ||
			!get_prot(otool, otool->ptr + section->offset, section->size))
			return (0);
	ft_vector_add(&otool->segment_32, &segment);
	return (1);
}

t_ret	verif_segment_64(t_otool *otool, void *ptr)
{
	struct segment_command_64	*segment;
	struct section_64			*section;
	uint64_t					i;

	if (!(segment = get_segment_command_64(otool, ptr)))
		return (0);
	i = (uint64_t)-1;
	while (++i < segment->nsects)
		if (!(section = get_section_64(otool, ptr +
			sizeof(struct segment_command_64) +
			i * sizeof(struct section_64))) ||
			!get_str(otool, (char*)&section->sectname) ||
			!get_prot(otool, otool->ptr + section->offset, section->size))
			return (0);
	ft_vector_add(&otool->segment_64, &segment);
	return (1);
}

t_ret	read_mach_32(t_otool *otool, void *ptr, char *name, t_file_type type)
{
	struct load_command	*cmd;
	struct mach_header	*header;
	uint64_t			i[2];

	if (!(header = get_mach_header(otool, ptr)))
		return (RETURN_FILE_CORRUPTED);
	if (type == TYPE_FAT)
		ft_printf("%s (architecture %s):\n", name,
		get_cpu_type(header->cputype));
	i[0] = 0;
	i[1] = (uint64_t)-1;
	ft_vector_resize(&otool->segment_32, 0);
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(otool, ptr + sizeof(struct mach_header) +
			i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if (cmd->cmd == LC_SEGMENT && !verif_segment_32(otool, cmd))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
	i[1] = (uint64_t)-1;
	while (++i[1] < otool->segment_32.n)
		read_segment(otool,
		*(struct segment_command**)ft_vector_get(&otool->segment_32, i[1]));
	return (RETURN_SUCCESS);
}

t_ret	read_mach_64(t_otool *otool, void *ptr, char *name, t_file_type type)
{
	struct load_command		*cmd;
	struct mach_header_64	*header;
	uint64_t				i[2];

	if (!(header = get_mach_header_64(otool, ptr)))
		return (RETURN_FILE_CORRUPTED);
	if (type == TYPE_FAT)
		ft_printf("%s (architecture %s):\n", name,
		get_cpu_type(header->cputype));
	i[0] = 0;
	i[1] = (uint64_t)-1;
	ft_vector_resize(&otool->segment_64, 0);
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(otool, ptr +
			sizeof(struct mach_header_64) + i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if (cmd->cmd == LC_SEGMENT_64 && !verif_segment_64(otool, cmd))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
	i[1] = (uint64_t)-1;
	while (++i[1] < otool->segment_64.n)
		read_segment_64(otool,
		*(struct segment_command_64**)ft_vector_get(&otool->segment_64, i[1]));
	return (RETURN_SUCCESS);
}

t_ret	read_mach(t_otool *otool, void *ptr, char *name, t_file_type type)
{
	uint32_t	*magic;

	if (!(magic = get_prot(otool, ptr, sizeof(uint32_t))))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
	{
		if (type == TYPE_MACH)
			ft_printf("%s:\n", name);
		return (read_mach_32(otool, ptr, name, type));
	}
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
	{
		if (type == TYPE_MACH)
			ft_printf("%s:\n", name);
		return (read_mach_64(otool, ptr, name, type));
	}
	return (RETURN_UNKNOWN_FILE_FORMAT);
}
