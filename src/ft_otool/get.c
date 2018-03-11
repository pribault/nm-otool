/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:35:19 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 16:49:08 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	*get_prot(t_otool *otool, void *ptr, size_t size)
{
	return ((ptr >= otool->ptr && otool->ptr + otool->size >= ptr + size) ?
	ptr : NULL);
}

char	*get_str(t_otool *otool, char *ptr)
{
	static char	buff[STR_MAX];
	size_t		i;

	i = (size_t)-1;
	while (get_prot(otool, ptr + ++i, 1) && i < STR_MAX)
		if ((buff[i] = ptr[i]) == '\0')
			return ((char*)&buff);
	return (NULL);
}

void	*get_fat_header(t_otool *otool, struct fat_header *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct fat_header)))
		return (NULL);
	if (ptr->magic == FAT_CIGAM || ptr->magic == FAT_CIGAM_64)
		otool->opt |= FAT_ENDIAN;
	else if (ptr->magic == FAT_MAGIC || ptr->magic == FAT_MAGIC_64)
		otool->opt &= ~FAT_ENDIAN;
	else
		return (NULL);
	if (otool->opt | FAT_ENDIAN)
	{
		endian(&ptr->magic, sizeof(uint32_t));
		endian(&ptr->nfat_arch, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_fat_arch(t_otool *otool, struct fat_arch *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct fat_arch)))
		return (NULL);
	if (otool->opt | FAT_ENDIAN)
	{
		endian(&ptr->cputype, sizeof(cpu_type_t));
		endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
		endian(&ptr->offset, sizeof(uint32_t));
		endian(&ptr->size, sizeof(uint32_t));
		endian(&ptr->align, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_fat_arch_64(t_otool *otool, struct fat_arch_64 *ptr)
{
	if (!get_prot(otool, ptr, sizeof(struct fat_arch_64)))
		return (NULL);
	if (otool->opt | FAT_ENDIAN)
	{
		endian(&ptr->cputype, sizeof(cpu_type_t));
		endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
		endian(&ptr->offset, sizeof(uint64_t));
		endian(&ptr->size, sizeof(uint64_t));
		endian(&ptr->align, sizeof(uint32_t));
		endian(&ptr->reserved, sizeof(uint32_t));
	}
	return (ptr);
}
