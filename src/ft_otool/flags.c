/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:12:39 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 20:12:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	get_default(char *file, t_otool *otool)
{
	ft_vector_add(&otool->files, &file);
}

void	print_usage(void)
{
	ft_printf("\e[2m./ft_otool\e[0m <file>\e[0m\n");
	ft_printf("  \e[1mavailable options:\e[0m\n");
	ft_printf("    \e[2m--help\e[0m or \e[2m-h\e[0m: print usage\n");
	ft_printf("    \e[2m--debug\e[0m\e[0m: enable debug mode\n");
	ft_printf("    \e[2m-t\e[0m: print text section\n");
	ft_printf("    \e[2m-d\e[0m: print data section\n");
	ft_printf("    \e[2m-b\e[0m: print bss section\n");
	exit(1);
}

void	set_debug(t_otool *otool)
{
	otool->opt |= DEBUG;
}

void	set_text_section(t_otool *otool)
{
	otool->opt ^= TEXT_SECTION;
}

void	set_data_section(t_otool *otool)
{
	otool->opt ^= DATA_SECTION;
}
