/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:13:23 by pribault          #+#    #+#             */
/*   Updated: 2018/03/31 18:16:36 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** includes
*/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <inttypes.h>
# include "ft_printf.h"

/*
** macros
*/

# define VECTOR_SIZE	4096
# define BUFF_SIZE 		4096

# define WHITESPACES	"\a\b\t\n\v\f\r "

# define BYTE(x)		((1 << x))

# define ERROR_EXIT		BYTE(0)

# define FLAG_PARAM_MAX	4

# define DEFAULT_VECTOR	(t_vector){0, 0, 0, 0, ALLOC_MALLOC}

# define DEFAULT_BUFFER	(t_circ_buffer){0, 0, 0, 0, 0, 0, 0, 0, ALLOC_MALLOC}

/*
** structures
*/

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef enum		e_alloc_type
{
	ALLOC_MALLOC,
	ALLOC_MMAP
}					t_alloc_type;

typedef struct		s_vector
{
	size_t			size;
	size_t			type;
	size_t			n;
	void			*ptr;
	t_alloc_type	alloc;
}					t_vector;

typedef struct		s_circ_buffer
{
	uint32_t		write_idx;
	uint32_t		read_idx;
	uint32_t		n;
	uint64_t		type;
	uint64_t		elems;
	void			*ptr;
	void			(*trash_callback)(void*, void*);
	void			*data;
	t_alloc_type	alloc;
}					t_circ_buffer;

typedef struct		s_gnl_stack
{
	char			line[BUFF_SIZE + 1];
	int				fd;
}					t_gnl_stack;

typedef enum		e_param_type
{
	PARAM_STR,
	PARAM_INTEGER,
	PARAM_UNSIGNED,
	PARAM_FLOAT,
	PARAM_MAX
}					t_param_type;

typedef struct		s_short_flag
{
	char			c;
	void			(*function)(void *data);
}					t_short_flag;

typedef struct		s_long_flag
{
	char			*str;
	int				n_params;
	t_param_type	params_type[FLAG_PARAM_MAX];
	void			(*function)(void *data, char **args, int n);
}					t_long_flag;

typedef struct		s_flags
{
	t_short_flag	*shorts;
	t_long_flag		*longs;
	void			(*def)(char *s, void *data);
}					t_flags;

typedef enum		e_default_error
{
	ERROR_ALLOCATION,
	ERROR_FILE,
	ERROR_UNKNOWN,
	ERROR_STR,
	ERROR_INTEGER,
	ERROR_UNSIGNED,
	ERROR_FLOAT,
	ERROR_CUSTOM,
	ERROR_NOT_ENOUGHT_PARAM,
	ERROR_TOO_MUSH_PARAMS,
	ERROR_UNKNOW_PARAMETER_TYPE,
	ERROR_UNKNOWN_PARAMETER,
	ERROR_UNKNOWN_SHORT_FLAG,
	ERROR_UNKNOWN_LONG_FLAG,
	ERROR_MMAP,
	ERROR_INVALID_FREE,
	ERROR_INVALID_POINTER,
	ERROR_FT_MAX
}					t_default_error;

typedef struct		s_error
{
	int				error_code;
	char			*format;
	uint8_t			opt;
}					t_error;

typedef struct		s_enum_func
{
	int				id;
	int				(*function)(void*);
}					t_enum_func;

typedef enum		e_bool
{
	FT_FALSE,
	FT_TRUE
}					t_bool;

/*
** prototypes
*/

void				ft_error(int fd, int error, void *param);
void				ft_add_errors(t_error *array);
void				ft_get_flags(int argc, char **argv, t_flags *flags,
					void *data);
t_flags				*ft_get_flag_array(t_short_flag *chars, t_long_flag *strs,
					void (*def)(char*, void*));
double				ft_atof(char *str);
int					ft_atoi(char *str);
int					ft_atoi_base(char *str, char *base);
unsigned int		ft_atou(char *str);
void				ft_bzero(void *s, size_t n);
char				*ft_execute(char *file, char **arg, char **env);
char				ft_get_all_lines(int fd, char **str);
int					ft_get_next_line(int const fd, char **line);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, char *base);
size_t				ft_nbrlen(int nbr);
size_t				ft_nbrlen_base(int nbr, int base);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strtolower(char *str);
char				*ft_strtoupper(char *str);

/*
**	write functions
*/

void				ft_putchar(char c);
void				ft_putwchar(wchar_t c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putstr(char const *s);
void				ft_putwstr(wchar_t const *s);
void				ft_showtab(char **tab);

void				ft_putchar_fd(char c, int fd);
void				ft_putwchar_fd(wchar_t c, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putwstr_fd(wchar_t const *s, int fd);

/*
**	test functions
*/

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isfloat(char *s);
int					ft_isinteger(char *s);
int					ft_isnumeric(char *s);
char				ft_isof(int c, char *str);
int					ft_isprime(int n);
int					ft_isprint(int c);
int					ft_isunsigned(char *s);

/*
**	maths functions
*/

int					ft_abs(int n);
float				ft_fabs(float n);
double				ft_dpower(double n, size_t power);
size_t				ft_factorial(size_t n);
double				ft_mod(double x, double m);
long				ft_power(long n, size_t power);
int					ft_rand(int min, int max);
int					ft_sqrt(int n);

/*
**	mem functions
*/

void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				ft_memdump(void *ptr, size_t size);
void				*ft_memdup(void *ptr, size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);

/*
**	array functions
*/

void				**ft_alloc_array(size_t h, size_t w, size_t size);
int					ft_arraylen(char **array);
void				ft_free_array(void **array, size_t len);
char				*ft_implode(char **array, char c);
char				**ft_ls(char *name);

/*
**	list functions
*/

void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
t_list				*ft_lstget(t_list *head, size_t n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
size_t				ft_lstlen(t_list *head);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstmove(t_list **head, size_t from, size_t to);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstprint(t_list *head, void (*print)(void*));
void				ft_lstput(t_list **head, t_list *new, size_t n);
void				ft_lstsort(t_list *head, int (*sort)(void*, void*));

/*
**	vector functions
*/

void				ft_vector_init(t_vector *vector, t_alloc_type alloc,
					size_t type);
void				ft_vector_del(t_vector *vector);
void				ft_vector_add(t_vector *vector, void *ptr);
void				ft_vector_del_one(t_vector *vector, size_t i);
void				*ft_vector_get(t_vector *vector, size_t n);
void				ft_vector_printhex(t_vector *vector);
void				ft_vector_resize(t_vector *vector, size_t new_size);

/*
**	circular buffer functions
*/

void				ft_circ_buffer_init(t_circ_buffer *buffer,
					t_alloc_type alloc, uint64_t type_size,
					uint64_t n_elements);
void				ft_circ_buffer_del(t_circ_buffer *buffer);
void				ft_circ_buffer_enqueue(t_circ_buffer *buffer, void *data);
void				*ft_circ_buffer_dequeue(t_circ_buffer *dequeue);
void				*ft_circ_buffer_get(t_circ_buffer *buffer, uint32_t idx);
uint64_t			ft_circ_buffer_get_size(t_circ_buffer *buffer);
void				ft_circ_buffer_set_trash_callback(t_circ_buffer *buffer,
					void (*callback)(void*, void*), void *data);

/*
**	string functions
*/

char				*ft_get_file_name_from_path(char *path);
char				*ft_getenv(char **env, char *name);
char				**ft_multisplit(char *str, char *sep);
char				*ft_reduce_path(char *path);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
size_t				ft_wstrlen(const wchar_t *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *str, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *big, const char *little, size_t l);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_swap(void *a, void *b, size_t size);

/*
**	global variables
*/

extern t_error		g_default_errors[];
extern t_error		*g_ft_errors;

#endif
