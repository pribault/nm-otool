/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:56:04 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 16:57:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*get_uint32(t_otool *otool, uint32_t *ptr)
{
	if (!get_prot(otool, ptr, sizeof(uint32_t)))
		return (NULL);
	if (ENDIAN(otool->opt))
		endian(ptr, sizeof(uint32_t));
	return (ptr);
}

void	*get_mach_header(t_otool *otool, struct mach_header *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct mach_header)))
		return (NULL);
	if (ptr->magic == MH_CIGAM)
		otool->opt |= MACH_ENDIAN;
	else if (ptr->magic == MH_MAGIC)
		otool->opt &= ~MACH_ENDIAN;
	else
		return (NULL);
	if (ENDIAN(otool->opt))
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

void	*get_mach_header_64(t_otool *otool, struct mach_header_64 *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct mach_header_64)))
		return (NULL);
	if (ptr->magic == MH_CIGAM_64)
		otool->opt |= MACH_ENDIAN;
	else if (ptr->magic == MH_MAGIC_64)
		otool->opt &= ~MACH_ENDIAN;
	if (ENDIAN(otool->opt))
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

void	*get_load_command(t_otool *otool, struct load_command *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct load_command)))
		return (NULL);
	if (ENDIAN(otool->opt))
	{
		endian(&ptr->cmd, sizeof(uint32_t));
		endian(&ptr->cmdsize, sizeof(uint32_t));
	}
	return (ptr);
}
