/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 11:41:36 by pribault          #+#    #+#             */
/*   Updated: 2018/05/04 18:02:19 by pribault         ###   ########.fr       */
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
# include <mach-o/ranlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/arch.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <ar.h>

# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define MACH_ENDIAN	BYTE(0)
# define FAT_ENDIAN		BYTE(1)
# define DEBUG			BYTE(2)
# define NO_SORT		BYTE(3)
# define REVERSE		BYTE(4)
# define NUMERIC_SORT	BYTE(5)
# define ONLY_UNDEFINED	BYTE(6)
# define NO_UNDEFINED	BYTE(7)
# define ONLY_GLOBAL	BYTE(8)
# define LOCAL_ARCH		BYTE(9)
# define ENDIAN(x)		(x & MACH_ENDIAN)

# define STR_MAX		128

# define SAVE_LINE		128

# define HOST_ARCH		CPU_TYPE_X86_64

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
	ERROR_ON_FD,
	ERROR_EMPTY_FILE,
	ERROR_GETTING_ARCH,
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
	t_vector	files;
	void		*ptr;
	size_t		size;
	t_vector	syms_32;
	t_vector	syms_64;
	t_vector	sect_32;
	t_vector	sect_64;
	uint32_t	stroff;
	uint32_t	opt;
	int			out;
	int			null;
	int			pipe[2];
	void		*buffer;
	size_t		buffer_size;
}				t_nm;

/*
******************
**	prototypes  **
******************
*/

void			reset_nm(t_nm *nm);

void			sort_symtab_32(t_nm *nm);
void			sort_symtab_64(t_nm *nm);
void			sort_symtab_32_function(t_nm *nm,
				int (*function)(t_nm *, struct nlist *, struct nlist *));
void			sort_symtab_64_function(t_nm *nm,
				int (*function)(t_nm *, struct nlist_64 *, struct nlist_64 *));
int				sort_symbol_32_alpha(t_nm *nm, struct nlist *a,
				struct nlist *b);
int				sort_symbol_64_alpha(t_nm *nm, struct nlist_64 *a,
				struct nlist_64 *b);
int				sort_symbol_32_numeric(t_nm *nm, struct nlist *a,
				struct nlist *b);
int				sort_symbol_64_numeric(t_nm *nm, struct nlist_64 *a,
				struct nlist_64 *b);
void			reverse_symtab_32(t_nm *nm);
void			reverse_symtab_64(t_nm *nm);

void			print_symtab_32(t_nm *nm);
void			print_symtab_64(t_nm *nm);

char			get_symbol_value_32(t_nm *nm, struct nlist *nlist);
char			get_symbol_value_64(t_nm *nm, struct nlist_64 *nlist);

/*
**	flag functions
*/

void			print_usage(void);
void			get_default(char *file, t_nm *nm);
void			get_file(char *file, t_nm *nm);
void			set_debug(t_nm *nm);
void			set_no_sort(t_nm *nm);
void			set_reverse(t_nm *nm);
void			set_numeric_sort(t_nm *nm);
void			set_only_undefined(t_nm *nm);
void			set_no_undefined(t_nm *nm);
void			set_only_global(t_nm *nm);

/*
**	memory functions
*/

void			*get_prot(t_nm *nm, void *ptr, size_t size);
char			*get_str(t_nm *nm, char *ptr);
void			*get_uint32(t_nm *nm, uint32_t *ptr);

void			*get_fat_header(t_nm *nm, struct fat_header *ptr);

void			*get_fat_arch(t_nm *nm, struct fat_arch *ptr);
void			*get_fat_arch_64(t_nm *nm, struct fat_arch_64 *ptr);

void			*get_mach_header(t_nm *nm, struct mach_header *ptr);
void			*get_mach_header_64(t_nm *nm, struct mach_header_64 *ptr);

void			*get_load_command(t_nm *nm, struct load_command *ptr);

void			*get_symtab_command(t_nm *nm, struct symtab_command *ptr);

void			*get_segment_command(t_nm *nm, struct segment_command *ptr);
void			*get_segment_command_64(t_nm *nm,
				struct segment_command_64 *ptr);

void			*get_section(t_nm *nm, struct section *ptr);
void			*get_section_64(t_nm *nm, struct section_64 *ptr);

void			*get_nlist(t_nm *nm, struct nlist *ptr);
void			*get_nlist_64(t_nm *nm, struct nlist_64 *ptr);

char			*get_cpu_type(cpu_type_t type);

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

t_ret			read_segment(t_nm *nm, void *ptr);
t_ret			read_segment_64(t_nm *nm, void *ptr);

/*
**	output functions
*/

void			clean_output(t_nm *nm);
void			save_output(t_nm *nm);
void			print_output(t_nm *nm);
void			print_output_to(t_nm *nm, int fd);

/*
**	debug functions
*/

void			debug_full(t_nm *nm);

/*
**	others
*/

char			*get_name(char *file);

extern t_long_flag	g_long_flags[];

#endif
