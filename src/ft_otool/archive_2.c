/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:34:04 by pribault          #+#    #+#             */
/*   Updated: 2018/03/11 16:34:32 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

char	*get_name(char *file)
{
	static char	name[17];
	size_t		i;

	i = 16;
	name[16] = '\0';
	while (--i != (size_t)-1)
	{
		if (file[i] == ' ')
			name[i] = '\0';
		else
			name[i] = file[i];
	}
	return ((char*)&name);
}
