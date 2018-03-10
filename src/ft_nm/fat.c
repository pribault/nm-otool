/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:47:38 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 17:55:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_ret	read_fat_32(t_nm *nm, void *ptr, char *name)
{
	void				*save_ptr;
	size_t				save_size;
	struct fat_arch		*arch;

	if (!(arch = get_fat_arch(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	save_ptr = nm->ptr;
	save_size = nm->size;
	nm->ptr = nm->ptr + arch->offset;
	nm->size -= (nm->ptr - save_ptr);
	if (read_mach(nm, nm->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
	{
		nm->ptr = save_ptr;
		nm->size = save_size;
		return (RETURN_FILE_CORRUPTED);
	}
	nm->ptr = save_ptr;
	nm->size = save_size;
	return (RETURN_SUCCESS);
}

t_ret	read_fat_64(t_nm *nm, void *ptr, char *name)
{
	void				*save_ptr;
	size_t				save_size;
	struct fat_arch_64	*arch;

	if (!(arch = get_fat_arch_64(nm, ptr)))
		return (RETURN_FILE_CORRUPTED);
	save_ptr = nm->ptr;
	save_size = nm->size;
	nm->ptr = nm->ptr + arch->offset;
	nm->size -= (nm->ptr - save_ptr);
	if (read_mach(nm, nm->ptr, name, TYPE_FAT) !=
		RETURN_SUCCESS)
	{
		nm->ptr = save_ptr;
		nm->size = save_size;
		return (RETURN_FILE_CORRUPTED);
	}
	nm->ptr = save_ptr;
	nm->size = save_size;
	return (RETURN_SUCCESS);
}

t_ret	read_fat(t_nm *nm, void *ptr, char *name)
{
	struct fat_header	*fat;
	uint32_t			i;

	if (!(fat = get_fat_header(nm, ptr)))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	i = (uint32_t)-1;
	if (fat->magic == FAT_MAGIC)
	{
		while (++i < fat->nfat_arch)
			if (read_fat_32(nm, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
	}
	else if (fat->magic == FAT_MAGIC_64)
	{
		while (++i < fat->nfat_arch)
			if (read_fat_64(nm, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch_64), name) != RETURN_SUCCESS)
				return (RETURN_FILE_CORRUPTED);
	}
	else
		return (RETURN_UNKNOWN_FILE_FORMAT);
	return (RETURN_SUCCESS);
}
