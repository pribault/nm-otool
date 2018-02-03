/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 22:02:35 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:07:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	endian(void *ptr, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = size - 1;
	while (i < j)
	{
		((uint8_t*)ptr)[i] ^= ((uint8_t*)ptr)[j];
		((uint8_t*)ptr)[j] ^= ((uint8_t*)ptr)[i];
		((uint8_t*)ptr)[i++] ^= ((uint8_t*)ptr)[j--];
	}
}

void	*get_fat_header(t_nm *nm, struct fat_header *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct fat_header)))
		return (NULL);
	if (ptr->magic == FAT_CIGAM || ptr->magic == FAT_CIGAM_64)
		nm->opt ^= ENDIAN;
	if (nm->opt | ENDIAN)
	{
		endian(&ptr->magic, sizeof(uint32_t));
		endian(&ptr->nfat_arch, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_fat_arch(t_nm *nm, struct fat_arch *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct fat_arch)))
		return (NULL);
	if (nm->opt | ENDIAN)
	{
		endian(&ptr->cputype, sizeof(cpu_type_t));
		endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
		endian(&ptr->offset, sizeof(uint32_t));
		endian(&ptr->size, sizeof(uint32_t));
		endian(&ptr->align, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_fat_arch_64(t_nm *nm, struct fat_arch_64 *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct fat_arch_64)))
		return (NULL);
	if (nm->opt | ENDIAN)
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
