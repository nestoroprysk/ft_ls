#include <liblogic.h>
#include <libft.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

bool is_dir(mode_t type);
bool is_reg_file(mode_t type);
bool is_true(mode_t type);

typedef bool (*is_file_type_func)(mode_t s);

char get_file_type(t_file_node* n)
{
	static char file_type_char[NB_FILE_TYPES] = { 'd', '-' };
	return file_type_char[define_file_type(n->info.path, n->info.name)];
}

enum file_type define_file_type(const char* path, const char* file_name)
{
	static is_file_type_func is_file_type[NB_FILE_TYPES] =
											{is_dir,is_reg_file};
	assert(path && file_name);
	char* str = ft_strjoin(path, file_name);
	struct stat file_info;
	assert(stat(str, &file_info) == 0);
	mode_t type = file_info.st_mode;
	for (size_t i = 0; i < NB_FILE_TYPES; ++i)
	{
		if (is_file_type[i](type))
		{
			free(str);
			return i;
		}
	}
	free(str);
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
