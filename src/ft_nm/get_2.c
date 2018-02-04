/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 10:00:46 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 14:27:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*get_mach_header(t_nm *nm, struct mach_header *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct mach_header)))
		return (NULL);
	if (ptr->magic == MH_CIGAM)
		nm->opt &= ~MACH_ENDIAN;
	else if (ptr->magic == MH_MAGIC)
		nm->opt |= MACH_ENDIAN;
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->magic, sizeof(uint32_t));
		endian(&ptr->cputype, sizeof(cpu_type_t));
		endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
		endian(&ptr->filetype, sizeof(uint32_t));
		endian(&ptr->ncmds, sizeof(uint32_t));
		endian(&ptr->sizeofcmds, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_mach_header_64(t_nm *nm, struct mach_header_64 *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct mach_header_64)))
		return (NULL);
	if (ptr->magic == MH_CIGAM_64)
		nm->opt &= ~MACH_ENDIAN;
	else if (ptr->magic == MH_MAGIC_64)
		nm->opt |= MACH_ENDIAN;
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->magic, sizeof(uint32_t));
		endian(&ptr->cputype, sizeof(cpu_type_t));
		endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
		endian(&ptr->filetype, sizeof(uint32_t));
		endian(&ptr->ncmds, sizeof(uint32_t));
		endian(&ptr->sizeofcmds, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
		endian(&ptr->reserved, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_load_command(t_nm *nm, struct load_command *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct load_command)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->cmd, sizeof(uint32_t));
		endian(&ptr->cmdsize, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_symtab_command(t_nm *nm, struct symtab_command *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct symtab_command)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->symoff, sizeof(uint32_t));
		endian(&ptr->nsyms, sizeof(uint32_t));
		endian(&ptr->stroff, sizeof(uint32_t));
		endian(&ptr->strsize, sizeof(uint32_t));
	}
	return (ptr);
}
