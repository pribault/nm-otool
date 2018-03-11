/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 21:25:16 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 21:38:33 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_ret	print_text_section_32_endian(t_otool *otool, struct section *section,
		void *ptr, size_t size)
{
	size_t	i;

	if (!get_prot(otool, ptr, size))
		return (0);
	ft_printf("Contents of (%s,%s) section\n", &section->segname,
	&section->sectname);
	i = 0;
	while (i + 3 < size)
	{
		if (i && !(i % SAVE_LINE))
			save_output(otool);
		if (!(i % 16))
			ft_printf("%.8x\t", section->addr + i);
		endian(ptr + i, sizeof(uint32_t));
		ft_printf((!((i + 4) % 16)) ? "%.8x \n" : "%.8x ",
			*(uint32_t*)(ptr + i));
		i += 4;
	}
	if (i % 16)
		ft_putchar('\n');
	return (1);
}

t_ret	print_text_section_64_endian(t_otool *otool,
		struct section_64 *section, void *ptr, size_t size)
{
	size_t	i;

	if (!get_prot(otool, ptr, size))
		return (0);
	ft_printf("Contents of (%s,%s) section\n", &section->segname,
	&section->sectname);
	i = 0;
	while (i + 3 < size)
	{
		if (i && !(i % SAVE_LINE))
			save_output(otool);
		if (!(i % 16))
			ft_printf("%.8x\t", section->addr + i);
		endian(ptr + i, sizeof(uint32_t));
		ft_printf((!((i + 4) % 16)) ? "%.8x \n" : "%.8x ",
			*(uint32_t*)(ptr + i));
		i += 4;
	}
	if (i % 16)
		ft_putchar('\n');
	return (1);
}
