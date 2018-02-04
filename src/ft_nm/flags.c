/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:16:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 17:00:05 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	get_default(char *file, t_nm *nm)
{
	ft_vector_add(nm->files, &file);
}

void	print_usage(void)
{
	static t_bool	is_printed = FT_FALSE;

	if (is_printed)
		return ;
	is_printed = FT_TRUE;
	ft_printf("./ft_nm <file>\n");
}
