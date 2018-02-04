/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:41:36 by pribault          #+#    #+#             */
/*   Updated: 2018/02/04 18:58:19 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

/*
****************
**	includes  **
****************
*/

# include <mach/machine.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define MACH_ENDIAN	BYTE(0)
# define FAT_ENDIAN		BYTE(1)
# define ENDIAN(x)		((x & MACH_ENDIAN) ^ ((x & FAT_ENDIAN) >> 1))

# define STR_MAX		128

/*
*************
**	enums  **
*************
*/

typedef enum	e_nm_error
{
	ERROR_FSTAT = ERROR_FT_MAX,
	ERROR_MUNMAP,
	ERROR_UNKNOWN_FILE_FORMAT,
	ERROR_FILE_CORRUPTED,
	ERROR_NM_MAX
}				t_nm_error;

typedef enum	e_ret
{
	RETURN_SUCCESS,
	RETURN_UNKNOWN_FILE_FORMAT = ERROR_UNKNOWN_FILE_FORMAT,
	RETURN_FILE_CORRUPTED = ERROR_FILE_CORRUPTED
}				t_ret;

typedef enum	e_file_type
{
	TYPE_AR,
	TYPE_MACH,
	TYPE_FAT,
}				t_file_type;

/*
******************
**	structures  **
******************
*/

typedef struct	s_nm
{
	t_vector	*files;
	void		*ptr;
	size_t		size;
	t_vector	*syms_32;
	t_vector	*syms_64;
	t_vector	*sect_32;
	t_vector	*sect_64;
	t_vector	*out;
	uint32_t	stroff;
	uint8_t		opt;
}				t_nm;

/*
******************
**	prototypes  **
******************
*/

void			sort_symtab_32(t_nm *nm);
void			sort_symtab_64(t_nm *nm);

void			print_symtab_32(t_nm *nm);
void			print_symtab_64(t_nm *nm);

/*
**	flag functions
*/

void			print_usage(void);
void			get_default(char *file, t_nm *nm);
void			get_file(char *file, t_nm *nm);

/*
**	memory functions
*/

void			*get_prot(t_nm *nm, void *ptr, size_t size);
char			*get_str(t_nm *nm, char *ptr);

void			*get_fat_header(t_nm *nm, struct fat_header *ptr);
void			*get_fat_arch(t_nm *nm, struct fat_arch *ptr);
void			*get_fat_arch_64(t_nm *nm, struct fat_arch_64 *ptr);
void			*get_mach_header(t_nm *nm, struct mach_header *ptr);
void			*get_mach_header_64(t_nm *nm, struct mach_header_64 *ptr);
void			*get_load_command(t_nm *nm, struct load_command *ptr);
void			*get_symtab_command(t_nm *nm, struct symtab_command *ptr);

/*
**	endian functions
*/

void			endian(void *ptr, size_t size);
void			*endian_nlist(t_nm *nm, struct nlist *ptr);
void			*endian_nlist_64(t_nm *nm, struct nlist_64 *ptr);

/*
**	read functions
*/

t_ret			read_fat(t_nm *nm, void *ptr, char *name);
t_ret			read_mach(t_nm *nm, void *ptr, char *name,
				t_file_type type);
t_ret			read_ar(t_nm *nm, void *ptr, char *name);

/*
**	output functions
*/

void			add_to_output(t_vector *out, char *s);
void			clean_output(t_vector *out);
void			print_output(t_vector *out);

#endif
