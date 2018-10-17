#include <liblogic.h>
#include <libft.h>
#include <stdlib.h>
#include <assert.h>

static bool is_root_dir(mode_t type, const char* file_name);
static bool is_dir(mode_t type, const char* file_name);
static bool is_reg_file(mode_t type, const char* file_name);

typedef bool (*is_file_type_func)(mode_t s, const char* file_name);

char get_file_type_char(t_file_node* n)
{
	static char file_type_char[NB_FILE_TYPES] = { 'd', 'd', '-' };
	return file_type_char[define_file_type(n->info.full_name)];
}

enum file_type define_file_type(const char* full_name)
{
	static is_file_type_func is_file_type[NB_FILE_TYPES] =
									{ is_root_dir, is_dir, is_reg_file };
	assert(full_name);
	struct stat file_info;
	assert(stat(full_name, &file_info) == 0);
	mode_t type = file_info.st_mode;
	for (size_t i = 0; i < NB_FILE_TYPES; ++i)
		if (is_file_type[i](type, full_name))
			return i;
	return other_file_type;
}

static bool is_root_dir(mode_t type, const char* file_name)
{
	return S_ISDIR(type) &&
		(ft_strequ(file_name, ".") || ft_strequ(file_name, ".."));
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
