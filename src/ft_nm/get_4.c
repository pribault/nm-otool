/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 11:10:12 by pribault          #+#    #+#             */
/*   Updated: 2018/02/25 13:47:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	*get_cpu_type_2(cpu_type_t type)
{
	if (type == CPU_TYPE_I860)
		return ("i860");
	if (type == CPU_TYPE_POWERPC)
		return ("ppc");
	if (type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	return ("unknown");
}

char	*get_cpu_type(cpu_type_t type)
{
	if (type == CPU_TYPE_ANY)
		return ("any");
	if (type == CPU_TYPE_VAX)
		return ("vax");
	if (type == CPU_TYPE_I386)
		return ("i386");
	if (type == CPU_TYPE_X86)
		return ("x86");
	if (type == CPU_TYPE_X86_64)
		return ("x86_64");
	if (type == CPU_TYPE_MC680x0)
		return ("mc680x0");
	if (type == CPU_TYPE_MC98000)
		return ("mc98000");
	if (type == CPU_TYPE_HPPA)
		return ("hppa");
	if (type == CPU_TYPE_ARM)
		return ("arm");
	if (type == CPU_TYPE_ARM64)
		return ("arm64");
	if (type == CPU_TYPE_MC88000)
		return ("mc88000");
	if (type == CPU_TYPE_SPARC)
		return ("sparc");
	return (get_cpu_type_2(type));
}

void	*get_nlist(t_nm *nm, struct nlist *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct nlist)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->n_un, sizeof(ptr->n_un));
		endian(&ptr->n_type, sizeof(uint8_t));
		endian(&ptr->n_sect, sizeof(uint8_t));
		endian(&ptr->n_desc, sizeof(uint16_t));
		endian(&ptr->n_value, sizeof(uint32_t));
	}
	return (ptr);
}

void	*get_nlist_64(t_nm *nm, struct nlist_64 *ptr)
{
	if (!get_prot(nm, ptr, sizeof(struct nlist_64)))
		return (NULL);
	if (ENDIAN(nm->opt))
	{
		endian(&ptr->n_un, sizeof(ptr->n_un));
		endian(&ptr->n_type, sizeof(uint8_t));
		endian(&ptr->n_sect, sizeof(uint8_t));
		endian(&ptr->n_desc, sizeof(uint16_t));
		endian(&ptr->n_value, sizeof(uint64_t));
	}
	return (ptr);
}
