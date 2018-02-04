/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:10:42 by pribault          #+#    #+#             */
/*   Updated: 2017/11/02 12:26:16 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_ls(char *dir)
{
	char			**files;
	struct dirent	*dirent;
	DIR				*ptr;
	size_t			i;

	if (!(ptr = opendir(dir)) ||
		!(files = (char**)malloc(sizeof(char*))))
		return (NULL);
	i = 0;
	while ((dirent = readdir(ptr)))
		if (!(files = (char**)realloc(files, sizeof(char*) * (i + 2))) ||
			!(files[i++] = ft_strdup(dirent->d_name)))
			return (NULL);
	files[i] = NULL;
	closedir(ptr);
	return (files);
}
