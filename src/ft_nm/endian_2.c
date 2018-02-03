/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 00:12:50 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:27:41 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	*endian_mach_header(struct mach_header *ptr)
{
	endian(&ptr->magic, sizeof(uint32_t));
	endian(&ptr->cputype, sizeof(cpu_type_t));
	endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
	endian(&ptr->filetype, sizeof(uint32_t));
	endian(&ptr->ncmds, sizeof(uint32_t));
	endian(&ptr->sizeofcmds, sizeof(uint32_t));
	endian(&ptr->flags, sizeof(uint32_t));
	return (ptr);
}

void	*endian_mach_header_64(struct mach_header_64 *ptr)
{
	endian(&ptr->magic, sizeof(uint32_t));
	endian(&ptr->cputype, sizeof(cpu_type_t));
	endian(&ptr->cpusubtype, sizeof(cpu_subtype_t));
	endian(&ptr->filetype, sizeof(uint32_t));
	endian(&ptr->ncmds, sizeof(uint32_t));
	endian(&ptr->sizeofcmds, sizeof(uint32_t));
	endian(&ptr->flags, sizeof(uint32_t));
	endian(&ptr->reserved, sizeof(uint32_t));
	return (ptr);
}
