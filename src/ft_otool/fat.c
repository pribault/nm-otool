/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:46:54 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 16:11:01 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_ret	read_fat_32(t_otool *otool, void *ptr, char *name)
{
	void				*save_ptr;
	size_t				save_size;
	struct fat_arch		*arch;

	if (!(arch = get_fat_arch(otool, ptr)))
		return (RETURN_FILE_CORRUPTED);
	save_ptr = otool->ptr;
	save_size = otool->size;
	otool->ptr = otool->ptr + arch->offset;
	otool->size -= (otool->ptr - save_ptr);
	if (read_mach(otool, otool->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
	{
		otool->ptr = save_ptr;
		otool->size = save_size;
		return (RETURN_FILE_CORRUPTED);
	}
	otool->ptr = save_ptr;
	otool->size = save_size;
	return (RETURN_SUCCESS);
}

t_ret	read_fat_64(t_otool *otool, void *ptr, char *name)
{
	void				*save_ptr;
	size_t				save_size;
	struct fat_arch_64	*arch;

	if (!(arch = get_fat_arch_64(otool, ptr)))
		return (RETURN_FILE_CORRUPTED);
	save_ptr = otool->ptr;
	save_size = otool->size;
	otool->ptr = otool->ptr + arch->offset;
	otool->size -= (otool->ptr - save_ptr);
	if (read_mach(otool, otool->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
	{
		otool->ptr = save_ptr;
		otool->size = save_size;
		return (RETURN_FILE_CORRUPTED);
	}
	otool->ptr = save_ptr;
	otool->size = save_size;
	return (RETURN_SUCCESS);
}

t_ret	read_fat(t_otool *otool, void *ptr, char *name)
{
	struct fat_header	*fat;
	uint32_t			i;

	if (!(fat = get_fat_header(otool, ptr)))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	i = (uint32_t)-1;
	if (fat->magic == FAT_MAGIC)
	{
		while (++i < fat->nfat_arch)
			if (read_fat_32(otool, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
	}
	else if (fat->magic == FAT_MAGIC_64)
	{
		while (++i < fat->nfat_arch)
			if (read_fat_64(otool, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch_64), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
	}
	else
		return (RETURN_UNKNOWN_FILE_FORMAT);
	return (RETURN_SUCCESS);
}
