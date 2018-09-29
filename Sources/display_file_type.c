#include <display_file_type.h>
#include <display_files.h>
#include <stdio.h>
#include <stdbool.h>

#define NB_FILE_TYPES 3

enum FYLE_TYPE { FYLE_TYPE_BLK, FYLE_TYPE_CHR,
	FYLE_TYPE_DIR, FYLE_TYPE_FIFO, FYLE_TYPE_LNK,
	FYLE_TYPE_REG, FYLE_TYPE_SOCK };

bool is_dir(mode_t st_mode)
{
	return S_ISDIR(st_mode);
}

bool is_reg(mode_t st_mode)
{
	return S_ISREG(st_mode);
}

void print_dir()
{
	printf("dir");
}

void print_reg()
{
	printf("reg");
}

void print_other()
{
	printf("other");
}

bool (*is_file_state_func_ptr_array[NB_FILE_TYPES])(mode_t) =
	{ is_dir, is_reg, is_reg };

void (*print_file_state_func_ptr_array[NB_FILE_TYPES])() =
	{ print_dir, print_reg, print_other };

void display_file_type(mode_t st_mode)
{
	size_t i = 0;
	while (i < NB_FILE_TYPES)
	{
		if (is_file_state_func_ptr_array[i](st_mode))
		{
			print_file_state_func_ptr_array[i](i);
			return ;
		}
		i++;
	}
}
