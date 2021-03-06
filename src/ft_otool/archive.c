/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:32:36 by pribault          #+#    #+#             */
/*   Updated: 2018/05/03 18:20:57 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_ret	read_file_in_ar(char *lib, char *file, t_otool *otool)
{
	t_ret		ret;

	if (!ft_strcmp(file, SYMDEF_SORTED) || !ft_strcmp(file, SYMDEF))
		return (RETURN_SUCCESS);
	ft_printf("%s(%s):\n", lib, file);
	if ((ret = read_fat(otool, otool->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_mach(otool, otool->ptr, file, TYPE_AR)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	if ((ret = read_ar(otool, otool->ptr, file)) !=
		RETURN_UNKNOWN_FILE_FORMAT)
		return (ret);
	return (RETURN_UNKNOWN_FILE_FORMAT);
}

t_ret			restore_otool(t_otool *otool, void *ptr, size_t size,
				t_ret ret)
{
	otool->ptr = ptr;
	otool->size = size;
	return (ret);
}

static t_ret	read_ar_2(t_otool *otool, struct ar_hdr *header, char *name,
				uint64_t *save)
{
	if (!get_str(otool, (void*)header + sizeof(struct ar_hdr)))
		return (RETURN_FILE_CORRUPTED);
	otool->ptr = (void*)header + sizeof(struct ar_hdr) +
	ft_atou((void*)(&header->ar_name) + 3);
	otool->size = save[0] + save[1] - (uint64_t)otool->ptr;
	if (read_file_in_ar(name, (void*)header + sizeof(struct ar_hdr),
		otool) == RETURN_FILE_CORRUPTED)
		return (restore_otool(otool, (void*)save[0], save[1],
		RETURN_FILE_CORRUPTED));
		return (RETURN_SUCCESS);
}

static t_ret	read_ar_3(t_otool *otool, struct ar_hdr *header, char *name,
				uint64_t *save)
{
	otool->ptr = (void*)header + sizeof(struct ar_hdr);
	otool->size = save[0] + save[1] - (uint64_t)otool->ptr;
	if (read_file_in_ar(name, get_name((char*)&header->ar_name), otool))
		return (restore_otool(otool, (void*)save[0], save[1],
		RETURN_FILE_CORRUPTED));
		return (RETURN_SUCCESS);
}

/*
**	save[0]: pointer save
**	save[1]: size save
*/

t_ret			read_ar(t_otool *otool, void *ptr, char *name)
{
	struct ar_hdr	*header;
	char			*ar;
	uint64_t		save[2];

	if (!(ar = get_prot(otool, ptr, SARMAG)) ||
		ft_strncmp(ar, ARMAG, SARMAG))
		return (RETURN_UNKNOWN_FILE_FORMAT);
	save[0] = (uint64_t)otool->ptr;
	save[1] = otool->size;
	ft_printf("Archive : %s\n", name);
	while ((header = get_prot(otool, ptr + SARMAG, sizeof(struct ar_hdr))))
	{
		if (ft_strncmp((char*)&header->ar_fmag, ARFMAG, 2) ||
			!get_prot(otool, (void*)header + sizeof(struct ar_hdr),
			ft_atou((char*)&header->ar_size)))
			return (RETURN_FILE_CORRUPTED);
		if ((!ft_strncmp((char*)&header->ar_name, "#1/", 3) && read_ar_2(otool,
			header, name, (uint64_t*)&save) != RETURN_SUCCESS) ||
			(ft_strncmp((char*)&header->ar_name, "#1/", 3) && read_ar_3(otool,
			header, name, (uint64_t*)&save) != RETURN_SUCCESS))
			return (RETURN_FILE_CORRUPTED);
		restore_otool(otool, (void*)save[0], save[1], RETURN_SUCCESS);
		ptr += sizeof(struct ar_hdr) + ft_atou((char*)&header->ar_size);
	}
	return (RETURN_SUCCESS);
}
