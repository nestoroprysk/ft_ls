#include <liblogic.h>
#include <libft.h>
#include <sys/stat.h>
#include <assert.h>

bool is_dir(mode_t type);
bool is_reg_file(mode_t type);
bool is_true(mode_t type);

typedef bool (*is_file_type_func)(mode_t s);

static is_file_type_func is_file_type[NB_FILE_TYPES] =
	{is_dir,is_reg_file};

enum file_type define_file_type(const char* file_name)
{
	assert(file_name);
	struct stat file_info;
	assert(stat(file_name, &file_info) == 0);
	mode_t type = file_info.st_mode;
	for (size_t i = 0; i < NB_FILE_TYPES; ++i)
		if (is_file_type[i](type))
			return i;
	assert(false);
	return other_file_type;
}

bool is_dir(mode_t type)
{
	return S_ISDIR(type);
}

bool is_reg_file(mode_t type)
{
	return S_ISREG(type);
}
