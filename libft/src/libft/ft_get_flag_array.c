/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flag_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:34:38 by pribault          #+#    #+#             */
/*   Updated: 2018/02/02 13:07:17 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_flags	*ft_get_flag_array(t_short_flag *shorts, t_long_flag *longs,
		void (*def)(char*, void*))
{
	static t_flags	flags;

	flags.shorts = shorts;
	flags.longs = longs;
	flags.def = def;
	return (&flags);
}
