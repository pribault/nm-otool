/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:47:38 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:36:31 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		read_fat_32(t_nm *nm, void *ptr)
{
	struct fat_arch		*arch;

	if (!(arch = get_fat_arch(nm, ptr)) ||
		!read_mach(nm, nm->ptr + arch->offset))
		return (0);
	return (1);
}

int		read_fat_64(t_nm *nm, void *ptr)
{
	struct fat_arch_64	*arch;

	if (!(arch = get_fat_arch_64(nm, ptr)) ||
		!read_mach(nm, nm->ptr + arch->offset))
		return (0);
	return (1);
}

int		read_fat(t_nm *nm, void *ptr)
{
	struct fat_header	*fat;
	uint32_t			i;

	if (!(fat = get_fat_header(nm, ptr)))
		return (0);
	i = (uint32_t)-1;
	if (fat->magic == FAT_MAGIC)
	{
		while (++i < fat->nfat_arch)
			if (!read_fat_32(nm, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch)))
				return (0);
	}
	else if (fat->magic == FAT_MAGIC_64)
	{
		while (++i < fat->nfat_arch)
			if (!read_fat_64(nm, ptr + sizeof(struct fat_header) +
				i * sizeof(struct fat_arch_64)))
				return (0);
	}
	else
		return (0);
	return (1);
}
