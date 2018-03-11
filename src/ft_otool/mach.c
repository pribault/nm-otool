/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:51:52 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 21:45:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(otool, ptr + sizeof(struct mach_header) +
			i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if (cmd->cmd == LC_SEGMENT && !read_segment(otool, cmd))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
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
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(otool, ptr +
			sizeof(struct mach_header_64) + i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if (cmd->cmd == LC_SEGMENT_64 && !read_segment_64(otool, cmd))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
	return (RETURN_SUCCESS);
}

t_ret	read_mach(t_otool *otool, void *ptr, char *name, t_file_type type)
{
	uint32_t	*magic;

	if (type == TYPE_MACH)
		ft_printf("%s:\n", name);
	if (!(magic = get_prot(otool, ptr, sizeof(uint32_t))))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		return (read_mach_32(otool, ptr, name, type));
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		return (read_mach_64(otool, ptr, name, type));
	return (RETURN_UNKNOWN_FILE_FORMAT);
}
