/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:27:06 by pribault          #+#    #+#             */
/*   Updated: 2018/05/03 17:54:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_ret	read_segment(t_nm *nm, void *ptr)
{
	struct segment_command	*segment;
	struct section			*section;
	uint32_t				i;

	if (!(segment = get_segment_command(nm, ptr)))
		return (0);
	i = (uint32_t)-1;
	while (++i < segment->nsects)
	{
		if (!(section = get_section(nm, ptr + sizeof(struct segment_command) +
			i * sizeof(struct section))) ||
			!get_str(nm, (char*)&section->sectname))
			return (0);
		ft_vector_add(&nm->sect_32, section);
	}
	return (1);
}

t_ret	read_segment_64(t_nm *nm, void *ptr)
{
	struct segment_command_64	*segment;
	struct section_64			*section;
	uint64_t					i;

	if (!(segment = get_segment_command_64(nm, ptr)))
		return (0);
	i = (uint64_t)-1;
	while (++i < segment->nsects)
	{
		if (!(section = get_section_64(nm, ptr +
			sizeof(struct segment_command_64) + i *
			sizeof(struct section_64))) ||
			!get_str(nm, (char*)&section->sectname))
			return (0);
		ft_vector_add(&nm->sect_64, section);
	}
	return (1);
}
