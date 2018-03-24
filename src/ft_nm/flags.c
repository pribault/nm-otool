/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:16:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 19:09:10 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	get_default(char *file, t_nm *nm)
{
	ft_vector_add(&nm->files, &file);
}

void	print_usage(void)
{
	ft_printf("\e[2m./ft_nm\e[0m <file>\e[0m\n");
	ft_printf("  \e[1mavailable options:\e[0m\n");
	ft_printf("    \e[2m--help\e[0m or \e[2m-h\e[0m: print usage\n");
	ft_printf("    \e[2m--debug\e[0m or \e[2m-d\e[0m: enable debug mode\n");
	ft_printf("    \e[2m--nosort\e[0m or \e[2m-p\e[0m: don't sort\n");
	ft_printf("    \e[2m--reverse\e[0m or \e[2m-r\e[0m: reverse\n");
	ft_printf("    \e[2m--numeric\e[0m or \e[2m-n\e[0m: sort numerically\n");
	exit(1);
}

void	set_debug(t_nm *nm)
{
	nm->opt |= DEBUG;
}

void	set_no_sort(t_nm *nm)
{
	nm->opt |= NO_SORT;
}

void	set_reverse(t_nm *nm)
{
	nm->opt |= REVERSE;
}
