/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 17:12:53 by pribault          #+#    #+#             */
/*   Updated: 2018/05/04 18:06:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_ret	print_section_32(t_otool *otool, struct section *section,
		void *ptr, uint32_t size)
{
	uint32_t	i;

	if (!get_prot(otool, ptr, size))
		return (0);
	i = 0;
	ft_printf("Contents of (%s,%s) section\n", &section->segname,
	&section->sectname);
	while (i < size)
	{
		if (i && !(i % SAVE_LINE))
			save_output(otool);
		if (!(i % 16))
			ft_printf("%.8x\t", section->addr + i);
		ft_printf((!((i + 1) % 16)) ? "%.2x \n" : "%.2x ",
			*(uint8_t*)(ptr + i));
		i++;
	}
	if (i % 16)
		ft_putchar('\n');
	save_output(otool);
	return (1);
}

t_ret	print_section_64(t_otool *otool, struct section_64 *section,
		void *ptr, uint64_t size)
{
	uint64_t	i;

	if (!get_prot(otool, ptr, size))
		return (0);
	i = 0;
	ft_printf("Contents of (%s,%s) section\n", &section->segname,
	&section->sectname);
	while (i < size)
	{
		if (i && !(i % SAVE_LINE))
			save_output(otool);
		if (!(i % 16))
			ft_printf("%.16lx\t", section->addr + i);
		ft_printf((!((i + 1) % 16)) ? "%.2x \n" : "%.2x ",
			*(uint8_t*)(ptr + i));
		i++;
	}
	if (i % 16)
		ft_putchar('\n');
	save_output(otool);
	return (1);
}

t_ret	read_segment(t_otool *otool, void *ptr)
{
	struct segment_command	*segment;
	struct section			*section;
	uint32_t				i;

	if (!(segment = ptr))
		return (0);
	i = (uint32_t)-1;
	while (++i < segment->nsects)
		if (!(section = ptr + sizeof(struct segment_command)
			+ i * sizeof(struct section)))
			return (0);
		else if (((otool->opt & TEXT_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_TEXT)) ||
			((otool->opt & DATA_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_DATA)) ||
			((otool->opt & BSS_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_BSS)))
			if (((ENDIAN(otool->opt) && !print_section_32_endian(otool,
				section, otool->ptr + section->offset, section->size)) ||
				((!ENDIAN(otool->opt) && !print_section_32(otool,
				section, otool->ptr + section->offset, section->size)))))
				return (0);
	return (1);
}

t_ret	read_segment_64(t_otool *otool, void *ptr)
{
	struct segment_command_64	*segment;
	struct section_64			*section;
	uint64_t					i;

	if (!(segment = ptr))
		return (0);
	i = (uint64_t)-1;
	while (++i < segment->nsects)
		if (!(section = ptr + sizeof(struct segment_command_64) + i *
		sizeof(struct section_64)))
			return (0);
		else if (((otool->opt & TEXT_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_TEXT)) ||
			((otool->opt & DATA_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_DATA)) ||
			((otool->opt & BSS_SECTION) &&
			!ft_strcmp((char*)&section->sectname, SECT_BSS)))
			if (((ENDIAN(otool->opt) && !print_section_64_endian(otool,
				section, otool->ptr + section->offset, section->size)) ||
				((!ENDIAN(otool->opt) && !print_section_64(otool, section,
				otool->ptr + section->offset, section->size)))))
				return (0);
	return (1);
}
