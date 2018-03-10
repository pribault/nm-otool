/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:16:21 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 19:35:43 by pribault         ###   ########.fr       */
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
	exit(1);
}

void	set_debug(t_nm *nm)
{
	nm->opt |= DEBUG;
}
