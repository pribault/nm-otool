/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:50:45 by pribault          #+#    #+#             */
/*   Updated: 2018/05/04 17:54:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		read_symtab(t_nm *nm, void *ptr)
{
	struct symtab_command	*symtab;
	struct nlist			*nlist;
	uint32_t				i;

	if (!(symtab = get_symtab_command(nm, ptr)) ||
		!get_prot(nm, nm->ptr + symtab->symoff,
		sizeof(struct nlist) * symtab->nsyms) ||
		nm->stroff)
		return (0);
	i = (uint32_t)-1;
	nm->stroff = symtab->stroff;
	while (++i < symtab->nsyms)
	{
		if (!(nlist = get_nlist(nm, nm->ptr + symtab->symoff +
			i * sizeof(struct nlist))))
			return (0);
		if (get_str(nm, nm->ptr + symtab->stroff + nlist->n_un.n_strx))
			ft_vector_add(&nm->syms_32, nlist);
		else
			return (0);
	}
	return (1);
}

int		read_symtab_64(t_nm *nm, void *ptr)
{
	struct symtab_command	*symtab;
	struct nlist_64			*nlist;
	uint32_t				i;

	if (!(symtab = get_symtab_command(nm, ptr)) ||
		!get_prot(nm, nm->ptr + symtab->symoff,
		sizeof(struct nlist_64) * symtab->nsyms) ||
		nm->stroff)
		return (0);
	i = (uint32_t)-1;
	nm->stroff = symtab->stroff;
	while (++i < symtab->nsyms)
	{
		if (!(nlist = get_nlist_64(nm, nm->ptr + symtab->symoff +
			i * sizeof(struct nlist_64))))
			return (0);
		if (get_str(nm, nm->ptr + symtab->stroff + nlist->n_un.n_strx))
			ft_vector_add(&nm->syms_64, nlist);
	}
	return (1);
}

t_ret	read_mach_32(t_nm *nm, void *ptr, char *name, t_file_type type)
{
	struct load_command	*cmd;
	struct mach_header	*header;
	uint64_t			i[2];

	if (!(header = get_mach_header(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	if (type == TYPE_FAT && !(nm->opt & LOCAL_ARCH))
		ft_printf("\n%s (for architecture %s):\n", name,
		get_cpu_type(header->cputype));
	i[0] = 0;
	i[1] = (uint64_t)-1;
	nm->stroff = 0;
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(nm, ptr + sizeof(struct mach_header) +
			i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if ((cmd->cmd == LC_SYMTAB && !read_symtab(nm, cmd)) ||
			(cmd->cmd == LC_SEGMENT && !read_segment(nm, cmd)))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
	sort_symtab_32(nm);
	print_symtab_32(nm);
	debug_full(nm);
	return (RETURN_SUCCESS);
}

t_ret	read_mach_64(t_nm *nm, void *ptr, char *name, t_file_type type)
{
	struct load_command		*cmd;
	struct mach_header_64	*header;
	uint64_t				i[2];

	if (!(header = get_mach_header_64(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	if (type == TYPE_FAT && !(nm->opt & LOCAL_ARCH))
		ft_printf("\n%s (for architecture %s):\n", name,
		get_cpu_type(header->cputype));
	i[0] = 0;
	i[1] = (uint64_t)-1;
	nm->stroff = 0;
	while (++i[1] < header->ncmds)
		if (!(cmd = get_load_command(nm, ptr + sizeof(struct mach_header_64) +
			i[0])))
			return (RETURN_FILE_CORRUPTED);
		else if ((cmd->cmd == LC_SYMTAB && !read_symtab_64(nm, cmd)) ||
			(cmd->cmd == LC_SEGMENT_64 && !read_segment_64(nm, cmd)))
			return (RETURN_FILE_CORRUPTED);
		else
			i[0] += cmd->cmdsize;
	sort_symtab_64(nm);
	print_symtab_64(nm);
	debug_full(nm);
	return (RETURN_SUCCESS);
}

t_ret	read_mach(t_nm *nm, void *ptr, char *name, t_file_type type)
{
	uint32_t	*magic;

	if (nm->files.n > 1 && (type == TYPE_MACH ||
		(type == TYPE_FAT && (nm->opt & LOCAL_ARCH))))
		ft_printf("\n%s:\n", name);
	if (!(magic = get_prot(nm, ptr, sizeof(uint32_t))))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	ft_vector_resize(&nm->syms_32, 0);
	ft_vector_resize(&nm->sect_32, 0);
	ft_vector_resize(&nm->syms_64, 0);
	ft_vector_resize(&nm->sect_64, 0);
	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		return (read_mach_32(nm, ptr, name, type));
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		return (read_mach_64(nm, ptr, name, type));
	return (RETURN_UNKNOWN_FILE_FORMAT);
}
