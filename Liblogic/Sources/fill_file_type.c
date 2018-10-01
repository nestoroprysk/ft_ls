#include <liblogic.h>
#include <libft.h>
#include <sys/stat.h>
#include <assert.h>

bool is_dir(mode_t type);
bool is_reg_file(mode_t type);
bool is_true(mode_t type);

typedef bool (*is_file_type_func)(mode_t s);

static is_file_type_func is_file_type[NB_FILE_TYPES] =
	{is_dir,is_reg_file,is_true};

void mark_dir_type(t_file_node* file);
void mark_reg_file_file_type(t_file_node* file);
void mark_other_file_type(t_file_node* file);

typedef void (*mark_file_type_func)(t_file_node* file);

static mark_file_type_func mark_file_type[NB_FILE_TYPES] =
	{mark_dir_type,mark_reg_file_file_type,mark_other_file_type};

void fill_file_type(t_file_node* file, struct stat* s)
{
	mode_t type = s->st_mode;
	for (size_t i = 0; i < NB_FILE_TYPES; ++i)
	{
		if (is_file_type[i](type))
		{
			mark_file_type[i](file);
			break;
		}
	}
}

bool is_dir(mode_t type)
{
	return S_ISDIR(type);
}

bool is_reg_file(mode_t type)
{
	return S_ISREG(type);
}

bool is_true(mode_t type)
{
	(void)type;
	return true;
}

void mark_dir_type(t_file_node* file)
{
	assert(file);
	file->info.type = dir_file_type;
}

void mark_reg_file_file_type(t_file_node* file)
{
	assert(file);
	file->info.type = reg_file_file_type;
}

void mark_other_file_type(t_file_node* file)
{
	assert(file);
	file->info.type = other_file_type;
}
