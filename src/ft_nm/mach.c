/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:50:45 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 00:36:51 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		read_mach_32(t_nm *nm, void *ptr)
{
	struct mach_header	*header;
	t_bool				boolean;

	if (!(header = get_prot(nm, ptr, sizeof(struct mach_header))))
		return (0);
	boolean = FT_FALSE;
	if (header->magic == MH_CIGAM)
	{
		boolean = FT_TRUE;
		nm->opt ^= ENDIAN;
		endian_mach_header(header);
	}
	if (boolean)
		nm->opt ^= ENDIAN;
	return (1);
}

int		read_mach_64(t_nm *nm, void *ptr)
{
	struct mach_header_64	*header;
	t_bool					boolean;

	if (!(header = get_prot(nm, ptr, sizeof(struct mach_header_64))))
		return (0);
	boolean = FT_FALSE;
	if (header->magic == MH_CIGAM_64)
	{
		boolean = FT_TRUE;
		nm->opt ^= ENDIAN;
		endian_mach_header_64(header);
	}
	if (boolean)
		nm->opt ^= ENDIAN;
	return (1);
}

int		read_mach(t_nm *nm, void *ptr)
{
	uint32_t	*magic;

	if (!(magic = get_prot(nm, ptr, sizeof(uint32_t))))
		return (0);
	if (*magic == MH_MAGIC || *magic == MH_CIGAM)
		return (read_mach_32(nm, ptr));
	else if (*magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		return (read_mach_64(nm, ptr));
	return (0);
}
