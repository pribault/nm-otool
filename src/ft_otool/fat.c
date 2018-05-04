/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:46:54 by pribault          #+#    #+#             */
/*   Updated: 2018/05/04 18:26:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_ret	restore_otool(t_otool *otool, void *ptr, size_t size,
				t_ret ret)
{
	otool->ptr = ptr;
	otool->size = size;
	return (ret);
}

static t_ret	read_fat_32(t_otool *otool, void *ptr, char *name)
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
	if (arch->cputype == HOST_ARCH)
	{
		clean_output(otool);
		otool->opt |= LOCAL_ARCH;
	}
	if (read_mach(otool, otool->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
		return (restore_otool(otool, save_ptr, save_size,
			RETURN_FILE_CORRUPTED));
		return (restore_otool(otool, save_ptr, save_size, RETURN_SUCCESS));
}

static t_ret	read_fat_64(t_otool *otool, void *ptr, char *name)
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
	if (arch->cputype == HOST_ARCH)
	{
		clean_output(otool);
		otool->opt |= LOCAL_ARCH;
	}
	if (read_mach(otool, otool->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
		return (restore_otool(otool, save_ptr, save_size,
			RETURN_FILE_CORRUPTED));
		return (restore_otool(otool, save_ptr, save_size, RETURN_SUCCESS));
}

t_ret			read_fat(t_otool *otool, void *ptr, char *name)
{
	struct fat_header	*fat;
	uint32_t			i;

	if (!(fat = get_fat_header(otool, ptr)))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	i = (uint32_t)-1;
	while (++i < fat->nfat_arch && !(otool->opt & LOCAL_ARCH))
		if (fat->magic == FAT_MAGIC)
		{
			if (read_fat_32(otool, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
		}
		else if (fat->magic == FAT_MAGIC_64)
		{
			if (read_fat_64(otool, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch_64), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
		}
		else
			return (RETURN_UNKNOWN_FILE_FORMAT);
	return (RETURN_SUCCESS);
}
