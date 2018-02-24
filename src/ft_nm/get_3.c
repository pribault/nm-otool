/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:34:36 by pribault          #+#    #+#             */
/*   Updated: 2018/02/24 21:57:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*get_segment_command(t_nm *nm, struct segment_command *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct segment_command)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->vmaddr, sizeof(uint32_t));
		endian(&ptr->vmsize, sizeof(uint32_t));
		endian(&ptr->fileoff, sizeof(uint32_t));
		endian(&ptr->filesize, sizeof(uint32_t));
		endian(&ptr->maxprot, sizeof(vm_prot_t));
		endian(&ptr->initprot, sizeof(vm_prot_t));
		endian(&ptr->nsects, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_segment_command_64(t_nm *nm, struct segment_command_64 *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct segment_command_64)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->vmaddr, sizeof(uint64_t));
		endian(&ptr->vmsize, sizeof(uint64_t));
		endian(&ptr->fileoff, sizeof(uint64_t));
		endian(&ptr->filesize, sizeof(uint64_t));
		endian(&ptr->maxprot, sizeof(vm_prot_t));
		endian(&ptr->initprot, sizeof(vm_prot_t));
		endian(&ptr->nsects, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_section(t_nm *nm, struct section *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct section)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->addr, sizeof(uint32_t));
		endian(&ptr->size, sizeof(uint32_t));
		endian(&ptr->offset, sizeof(uint32_t));
		endian(&ptr->align, sizeof(uint32_t));
		endian(&ptr->reloff, sizeof(uint32_t));
		endian(&ptr->nreloc, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
		endian(&ptr->reserved1, sizeof(uint32_t));
		endian(&ptr->reserved2, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_section_64(t_nm *nm, struct section_64 *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct section_64)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->addr, sizeof(uint64_t));
		endian(&ptr->size, sizeof(uint64_t));
		endian(&ptr->offset, sizeof(uint32_t));
		endian(&ptr->align, sizeof(uint32_t));
		endian(&ptr->reloff, sizeof(uint32_t));
		endian(&ptr->nreloc, sizeof(uint32_t));
		endian(&ptr->flags, sizeof(uint32_t));
		endian(&ptr->reserved1, sizeof(uint32_t));
		endian(&ptr->reserved2, sizeof(uint32_t));
		endian(&ptr->reserved3, sizeof(uint32_t));
	}
	return (ptr);
}
