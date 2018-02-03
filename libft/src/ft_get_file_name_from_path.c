/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_name_from_path.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:22:06 by pribault          #+#    #+#             */
/*   Updated: 2018/02/03 17:24:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_file_name_from_path(char *path)
{
	size_t	len;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (--len != (size_t)-1)
		if (path[len] == '/')
			return (&path[len + 1]);
	return (path);
}
