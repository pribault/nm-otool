/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:50:45 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 19:02:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		read_symtab(t_nm *nm, void *ptr)
{
	struct symtab_command	*symtab;
	struct nlist			*nlist;
	uint32_t				i;

	if (!(symtab = get_symtab_command(nm, ptr)) ||
		!(nlist = get_prot(nm, nm->ptr + symtab->symoff,
		sizeof(struct nlist) * symtab->nsyms)))
		return (0);
	i = (uint32_t)-1;
	nm->stroff = symtab->stroff;
	while (++i < symtab->nsyms)
		if (get_str(nm, nm->ptr + symtab->stroff + nlist[i].n_un.n_strx))
			ft_vector_add(nm->syms_32, nlist + i);
		else
			return (0);
	return (1);
}

int		read_symtab_64(t_nm *nm, void *ptr)
{
	struct symtab_command	*symtab;
	struct nlist_64			*nlist;
	uint32_t				i;

	if (!(symtab = get_symtab_command(nm, ptr)) ||
		!(nlist = get_prot(nm, nm->ptr + symtab->symoff,
		sizeof(struct nlist_64) * symtab->nsyms)))
		return (0);
	i = (uint32_t)-1;
	nm->stroff = symtab->stroff;
	while (++i < symtab->nsyms)
	{
		if (get_str(nm, nm->ptr + symtab->stroff + nlist[i].n_un.n_strx))
			ft_vector_add(nm->syms_64, nlist + i);
		else
			return (0);
	}
	return (1);
}

t_ret	read_mach_32(t_nm *nm, void *ptr)
{
	struct load_command	*cmd;
	struct mach_header	*header;
	uint64_t			size;
	uint32_t			i;

	if (!(header = get_mach_header(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	size = 0;
	i = (uint32_t)-1;
	while (++i < header->ncmds)
	{
		if (!(cmd = get_load_command(nm, ptr + sizeof(struct mach_header) +
			size)))
			return (RETURN_FILE_CORRUPTED);
		if (cmd->cmd == LC_SYMTAB)
			if (!(read_symtab(nm, cmd)))
				return (RETURN_FILE_CORRUPTED);
		size += cmd->cmdsize;
	}
	sort_symtab_32(nm);
	print_symtab_32(nm);
	return (RETURN_SUCCESS);
}

t_ret	read_mach_64(t_nm *nm, void *ptr)
{
	struct load_command		*cmd;
	struct mach_header_64	*header;
	uint64_t				size;
	uint32_t				i;

	if (!(header = get_mach_header_64(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	size = 0;
	i = (uint32_t)-1;
	while (++i < header->ncmds)
	{
		if (!(cmd = get_load_command(nm, ptr + sizeof(struct mach_header_64) +
			size)))
			return (RETURN_FILE_CORRUPTED);
		if (cmd->cmd == LC_SYMTAB)
			if (!(read_symtab_64(nm, cmd)))
				return (RETURN_FILE_CORRUPTED);
		size += cmd->cmdsize;
	}
	sort_symtab_64(nm);
	print_symtab_64(nm);
	return (RETURN_SUCCESS);
}

t_ret	read_mach(t_nm *nm, void *ptr, char *name, t_file_type type)
{
	uint32_t	*magic;

	if (type == TYPE_MACH && nm->files->n > 1)
		add_to_output(nm->out, ft_joinf("\n%s:", name));
	if (!(magic = get_prot(nm, ptr, sizeof(uint32_t))))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		return (read_mach_32(nm, ptr));
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		return (read_mach_64(nm, ptr));
	return (RETURN_UNKNOWN_FILE_FORMAT);
}
