/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 19:06:53 by pribault          #+#    #+#             */
/*   Updated: 2018/03/24 19:24:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	set_numeric_sort(t_nm *nm)
{
	nm->opt |= NUMERIC_SORT;
}

void	set_only_undefined(t_nm *nm)
{
	nm->opt |= ONLY_UNDEFINED;
}

void	set_no_undefined(t_nm *nm)
{
	nm->opt |= NO_UNDEFINED;
}
