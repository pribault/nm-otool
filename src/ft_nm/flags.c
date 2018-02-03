/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:16:21 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 21:27:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_usage(void)
{
	static t_bool	is_printed = FT_FALSE;

	if (is_printed)
		return ;
	is_printed = FT_TRUE;
	ft_printf("./ft_nm <file>\n");
}
