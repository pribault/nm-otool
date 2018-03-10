/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 21:17:45 by pribault          #+#    #+#             */
/*   Updated: 2018/03/10 21:18:58 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
