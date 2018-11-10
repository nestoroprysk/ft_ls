#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

#define CURRENT_DIR "."
#define PREVIOUS_DIR ".."
#define NB_FILE_TYPES 9

static bool is_root_dir(mode_t type, const char* file_name);
static bool is_dir(mode_t type, const char* file_name);
static bool is_reg_file(mode_t type, const char* file_name);
static bool is_symbolic_link(mode_t type, const char* file_name);
static bool is_chr(mode_t type, const char* file_name);
static bool is_blk(mode_t type, const char* file_name);
static bool is_sock(mode_t type, const char* file_name);
static bool is_fifo(mode_t type, const char* file_name);
static bool is_true(mode_t type, const char* file_name);

typedef bool (*is_file_type_func)(mode_t s, const char* file_name);

char get_file_type_char(t_file_node* n)
{
	static char file_type_char[NB_FILE_TYPES] =
		{ 'd', 'd', '-', 'l', 'c', 'b', 's', 'p', '?' };
	assert(n && n->info.is_valid);
	return file_type_char[define_file_type(n)];
}

enum file_type define_file_type(const t_file_node* n)
{
	static is_file_type_func is_file_type[NB_FILE_TYPES] =
		{ is_root_dir, is_dir, is_reg_file, is_symbolic_link, is_chr, is_blk, is_sock, is_fifo, is_true };
	assert(n);
	mode_t type = n->raw_info.stat.st_mode;
	for (size_t i = 0; i < NB_FILE_TYPES; ++i)
		if (is_file_type[i](type, n->info.name.data))
			return i;
	return other_file_type;
}

static bool is_root_dir(mode_t type, const char* file_name)
{
	return S_ISDIR(type) &&
		(ft_strequ(file_name, CURRENT_DIR) ||
			ft_strequ(file_name, PREVIOUS_DIR));
}

static bool is_dir(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISDIR(type);
}

static bool is_reg_file(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISREG(type);
}

static bool is_symbolic_link(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISLNK(type);
}

static bool is_chr(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISCHR(type);
}

static bool is_blk(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISBLK(type);
}

static bool is_sock(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISSOCK(type);
}

static bool is_fifo(mode_t type, const char* file_name)
{
	(void)file_name;
	return S_ISFIFO(type);
}

static bool is_true(mode_t type, const char* file_name)
{
	(void)type;
	assert(file_name);
	return true;
}
